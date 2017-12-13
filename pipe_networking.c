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
  int msg = 1;
  
  read(fd, down_name, sizeof(int));
  remove("known");
  
  //set to_client to downstream
  * to_client = open(down_name, O_WRONLY);
  write(*to_client, &msg, sizeof(int));

  read(fd, &msg, sizeof(int));

  //WE GOOD
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
  
  mkfifo("client"); // private fifo
  char* nemo = "client";
  int msg = 0;
  int up_fd = open("known", O_WRONLY);
  write(up_fd, nemo, sizeof(nemo));

  int fd = open("client", O_RDONLY);
  read(fd, &msg, sizeof(int));
  if(msg == 2){

  
 
  

  
  return 0;
}
