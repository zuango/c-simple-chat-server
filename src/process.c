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

    if (pid == 0) {
        // RECEIVER
        unsigned char buf[2048];

        while (1) {
            int r = read(sock, buf, sizeof(buf));
            if (r <= 0) break;

            buf[r] = 0;
            printf("[peer] %s\n", buf);
            fflush(stdout);
        }

        close(sock);
        _exit(0);
    }

    // SENDER
    char msg[1024];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (!fgets(msg, sizeof(msg), stdin))
            break;

        write(sock, msg, strlen(msg));
    }

    close(sock);
    waitpid(pid, NULL, 0);
}
