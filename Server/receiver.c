/*------------ UDP SERVER del SERVER ------------*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h> /* fork */
#include <sys/types.h>  /* pid_t */
#include <arpa/inet.h>
#include <sys/stat.h>
 
#define RECV_PORT 9999 //porta locale di ricezione
#define PATH_DIR "/home/giuseppe/Scrivania/Progetto_Reti/server/ip/" //cartella dove verranno salvati i file IP.txt

int main() {
    int sockfd;
    struct sockaddr_in recv_addr, send_addr;
    socklen_t l = sizeof(send_addr);
    char line[100], time_calc[20], stringa[100], path_file[100];
    char* nomefile;
    FILE *fp;

	//Creo la socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        printf("\nErrore nell'apertura del socket");
        return -1;
    }

	//Setto parametri socket
    memset((char *) &recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port = htons(RECV_PORT);

	//Assegno un indirizzo locale alla socket, per stabilire da quale «IP:porta» si metterà in ascolto
    if(bind(sockfd, (struct sockaddr *) &recv_addr, sizeof(send_addr)) < 0) { 
        printf("\nErrore nel binding. Errore \n");
        return -1;
    }
  
    while(1) {   
        memset((char *) &recv_addr, 0, sizeof(recv_addr));
        recvfrom(sockfd, line, 99, 0, (struct sockaddr *)&send_addr, &l);

        nomefile = (char *) malloc(strlen(line) + 4);
		
		//Concateno nome file con l'estensione
        strcpy(nomefile, line);
        strcat(nomefile, ".txt");
        
        printf("%s\n", nomefile);

		//Calcolo l'orario attuale in sec del server
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);  
        sprintf(time_calc, "%d", ((tm.tm_hour*3600)+(tm.tm_min*60)+tm.tm_sec));
        
		strcpy(path_file, PATH_DIR);
		
		// Controllo se esiste il file
        if(access(path_file, F_OK) != -1) {
			strcat(path_file, nomefile);
			
            printf("path_file: %s\n", path_file);
			
            //elimino il file in quella directory 
            remove(path_file);

            //ricreo il file
            fp = fopen(path_file, "w");

			//Inserisco l'orario di registrazione nel file
            fputs(time_calc, fp);
            
            fclose(fp); //Chiudo il file
        } else {
            strcat(path_file, nomefile);
			
            fp = fopen(path_file, "w");
			
            fputs(time_calc, fp);

            fclose(fp);
        }
    }
}