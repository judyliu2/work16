#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  //upstream
  
  //Setup
  //make known pipe
  mkfifo("known");
  int fd = open("known", O_RDONLY);


  //Handshake
  int down_fd;
  char * down_name;
  read(fd, down_name, sizeof(int));
  close(fd);
  
  to_client = open(down_name, O_WRONLY);
  remove("known");
  close(to_client);

  open(down_name, O_WRONLY);
  write(to_client, 1,  4);
  close(to_client);
  
 
  return fd;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  i
  mkfifo("client");
  
  int * i = (int *) calloc (sizeof(int));
  i = to_server;

  
  int up_fd = open("known", O_WRONLY);
  read(fd[READ], p , sizeof(s));
  
  i = up_fd;

  
  write();

  
  return 0;
}
