/*------------ UDP SERVER del CLIENT ------------*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 9930 //Porta di ricezione

int main(void) {
	struct sockaddr_in si_me, si_other;
	int sockfd;
	socklen_t slen = sizeof(si_other);
	char buf[100];

	//Creo la socket
	if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		printf("ERRORE SOCKET");

	//Setto parametri socket
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//Assegno un indirizzo locale alla socket, per stabilire da quale «IP:porta» si metterà in ascolto
	if(bind(sockfd, (struct sockaddr *) &si_me, sizeof(si_me)) == -1)
		printf("ERRORE BIND");

	while(1) {
		if(recvfrom(sockfd, buf, 100, 0, (struct sockaddr *) &si_other, &slen) == -1) 
			printf("ERRORE NON RICEVO");
	
		printf("Pacchetto ricevuto da %s: %d\nData: %s\n\n",  inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
	}
	close(sockfd);
	return 0;
}
