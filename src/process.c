#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../include/crypto.h"
#include "../include/process.h"



void start_chat_loop(int sock)
{
  pid_t pid = fork();

  if(pid == 0) {
    // RECEIVER
    unsigned char buf[2048];
    unsigned char plain[2048];
    while(1){
      int r = read(sock, buf, sizeof(buf));
      if(r <= 0) break;

      size_t out_len = 0;
      if(decrypt_message(buf, r, plain, &out_len)){
        plain[out_len] = 0;
        printf("[peer] %s\n", plain);
      } else {
        printf("[!] tampered message\n");
      }
    }
    return;
  }

  char msg[1024];
  unsigned char enc[2048];
  while(1){
    printf("> ");
    fflush(stdout);
    if(!fgets(msg, sizeof(msg), stdin)) break;

    size_t enc_len = 0;
    encrypt_message((unsigned char*)msg, strlen(msg), enc, &enc_len);
    write(sock, enc, enc_len);
  }
  waitpid(pid, NULL, 0);
}
