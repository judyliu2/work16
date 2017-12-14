#include "pipe_networking.h"
#include <stdio.h>
#include <stdlib.h>

/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  //upstream
  
  //Setup
  //Server creates a FIFO and waits for a connection ("well known pipe")
  printf("Server: FIFO created\n");
  mkfifo("known", 0666);
  int fd = open("known", O_RDONLY);
  

  //Handshake
  //Server recieves client message and removes "well known pipe"
  int down_fd;
  char down_name[64];
  int msg = 1;
  
  read(fd, &down_name,sizeof(down_name));
  printf("Server: should receive 'cliento'\n");
  printf("Server: received: %s\n",down_name);
  remove("known");

  //Server connects to client FIFO, sending an acknowledgement message
  //set to_client to downstream
  * to_client = open(down_name, O_WRONLY);

  write(*to_client, &msg, sizeof(int));

  printf("Server: Message sent: %d \n", msg);
  
  //Operation
  read(fd, &msg, sizeof(int));
  printf("Server: Info exchange\n");
  printf("Server: Message received: %d\n", msg);
  
  //reset

  printf("Server: closes connection \n");
  //WE GOOD
 return fd;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {

  //make private FIFO
  
  mkfifo("cliento", 0666); 
  char nemo[64]="cliento";
  printf("Client: create private FIFO\n");

  //client connects to server and sends a private FiFO name and waits for server's response
  int msg = 0;
  *to_server = open("known", O_WRONLY);
  write(*to_server, &nemo, sizeof(nemo));

  //client receives message and removes private FiFO
  int fd = open("cliento", O_RDONLY);
  read(fd, &msg, sizeof(int));
  printf("Client: Message received: %d\n", msg);

  int msg2;
  //client receives message and removes private FiFO
  if(msg == 1){
    msg2 = 3;
    remove("cliento");
    open(nemo, O_WRONLY);
    write(*to_server, &msg2, sizeof(int));
    printf("Client: sending: %d\n", msg2);
  }

  //Operation
  printf("Client: Info exchange\n");
  read(fd, &msg, sizeof(int));
  printf("Client: Message received: %d\n", msg);
  
  //reset


  printf("Client: client exits\n");
  
  return fd;
}
