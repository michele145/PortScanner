#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


void control(char ip[], int *ports, int conn_status, int index){

  if(conn_status < 0)
	  printf("\nPort %d on IP %s is closed!", *(ports + index), ip);
  
  else
    printf("\nPort %d on IP %s is open!", *(ports + index), ip);

}


int main(void){

  int main_socket, connection_status, n_port, *ports;
  char ip[15];


  puts("Enter the IP:\n");
  scanf("%s", ip);

  puts("How many ports do you want to scan?\n");
  scanf("%d", &n_port);


  ports = (int *) malloc(n_port * sizeof(int));


  for(int i = 0; i < n_port; i++){
    printf("Enter port number [%d]: ", i + 1);
    scanf("%d", &*(ports + i));
  }

  for(int i = 0; i < n_port; i++){

    main_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define the socket socket
    struct sockaddr_in socket_address;

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr(ip);
    socket_address.sin_port = htons(*(ports + i));

    //check the connection
    connection_status = connect(main_socket, (struct sockaddr *) &socket_address, sizeof(socket_address));
    control(ip, ports, connection_status, i);

    close(main_socket);

  }

  free(ports);
  
  return 0;
}
