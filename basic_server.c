#include "pipe_networking.h"

char* upper( char * string){
  return strcat(string, "1");
}

int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
  printf("from_client %d", from_client);
  
  
    // open(from_client, O_RDONLY);
    // printf("from_client %d", from_client);
    char input[256];
    
    //read(from_client,input, sizeof(input));
    
    printf("input: %s\n", input);
    /*
    write(to_client, upper(input), sizeof(upper(input)));
    */
    
}
