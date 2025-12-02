#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "net.h"

int create_server(int port)
{
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr = {0};

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  bind(sock, (struct sockaddr*)&addr, sizeof(addr));
  listen(sock, 1);

  int client = accept(sock, NULL, NULL);


  close(sock);
  return client;
}

int create_client(char *ip, int port)
{
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr = {0};

  addr.sin_family = AF_INET;
  addr.sin_port   = htons(port);
  inet_pton(AF_INET, ip, &addr.sin_addr);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));

  return sock;
}

