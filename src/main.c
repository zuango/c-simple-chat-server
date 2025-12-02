#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/net.h"
#include "../include/process.h"

int main(int argc, char **argv)
{
  if(argc < 2) {
    printf("Usage:\n");
    printf("  %s -listen <port>\n", argv[0]);
    printf("  %s -connect <ip> <port>\n", argv[0]);
    return 1;
  }

  int sock;

  if(strcmp(argv[1], "-listen") == 0) {
    int port = atoi(argv[2]);
    printf("Listening on port %d...\n", port);
    sock = create_server(port);
    printf("Client Connected!\n");
  }
  else if(strcmp(argv[1], "-connect") == 0) {
    char *ip = argv[2];
    int port = atoi(argv[3]);
    printf("Connected to %s:%d\n", ip, port);
    sock = create_client(ip, port);
  }
  else {
    return 1;
  }

  start_chat_loop(sock);
  close(sock);
  return 0;
}
