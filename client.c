#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  printf("to_server: %d\n", to_server);
  
  while(1){
   
    printf("Enter input:\n");
    
    char input[256];
    fgets(input, sizeof(input) ,stdin);
    printf("input: %s", input);
    
    //open(to_server, O_WRONLY);
    write(to_server, input, sizeof(input));
    /*
    read(from_server, input, sizeof(input));
    printf("modified input: %s \n", input);
    */
  }
}
