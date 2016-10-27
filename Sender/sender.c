/*------------ UDP CLIENT del CLIENT ------------*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.43.156"
#define CLIENT_IP "192.168.43.135"

#define SEND_PORT 9999 //invio alla porta 9999 del destinatario

int main() {
	int sockfd;
    struct sockaddr_in recv_addr;
	
	//Creo la socket
    if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0) { 
		printf("\nErrore nell'apertura del socket");
      	return -1;
    }

	//Setto parametri socket
    memset(&recv_addr,0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    recv_addr.sin_port = htons(SEND_PORT);    
	
    printf("client[DEL CLIENT] avviato\n");
	
    while(1) {
		sleep(7); //Simulo l'attesa prima di reinviare la registrazione
		
      	/* random int fra 0 e 9 */
		int r = rand() % 10;
      
		if(r < 5) {
      		printf("INVIO IP..\n");
      		sendto(sockfd, CLIENT_IP, strlen(CLIENT_IP)+1, 0, (struct sockaddr *)&recv_addr, sizeof(recv_addr));
     	} else {
			printf("NON INVIO\n");
		}
	}
}
