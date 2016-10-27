/*------------ UDP CLIENT del SERVER ------------*/

#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/time.h>

#define BUFLEN 100
#define PORT 9930
#define PATH_DIR "/home/giuseppe/Scrivania/Progetto_Reti/server/ip/"
 
int main(void) {
    struct sockaddr_in si_other;
    int s, timecalc;
    socklen_t slen = sizeof(si_other);
    char send_buff[BUFLEN], file_buff[BUFLEN], path_file[1000];
    FILE *fp;

    //Creo la socket
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) { 
		printf("\nErrore nell'apertura del socket");
		return -1;
    }

	//Setto parametri socket
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    
    printf("client[SERVER] avviato\n");
   
    while(1) {
		/* Parametri posizione directory */
        DIR *p;
        struct dirent *pp; //struttura contenente il nome del file trovato .txt
        p = opendir(PATH_DIR);
        
        if(p != NULL) {            
			//Cerca file dentro la directory
            while((pp = readdir (p)) != NULL) {  
                int length = strlen(pp->d_name);
                                
				//Cerca file con estensione .txt
                if(strncmp(pp->d_name + length - 4, ".txt", 4) == 0) {
                                        
                    puts(pp->d_name); //Inserisce il nome del file dentro la struttura
                                        
                    //Concatento nomefile col suo path assoluto
                    strcpy(path_file, PATH_DIR);
                    strcat(path_file, pp->d_name);
                    
                    printf("nomefile: %s\n", path_file);
                    
					//Apro il file appena settato
                    fp = fopen(path_file, "r");
                    char* ip_addr = strtok(pp->d_name, "txt"); //separo nome file dalla sua estensione
                    
                    ip_addr[strlen(ip_addr)-1] = '\0'; //elimino ultimo carattere "." finale
                 
                    printf("IP: %s\n", ip_addr);
                    
					//la funzione inet_addr() converte il formato IPv4 in una sequenza binaria
                    if (inet_aton(ip_addr, &si_other.sin_addr) == 0) {
                        fprintf(stderr, "inet_aton() failed\n");
                        exit(1);
                    }
                    
                    fgets(file_buff, BUFLEN, (FILE*)fp); //prelevo la l'orario di registrazione del file
                                        
                    fclose(fp); //chiudo il file

                    int time_save = atoi(file_buff); //trasforma una stringa in int
                    
					//Calcolo l'orario attuale in sec del server
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);  
                    timecalc = ((tm.tm_hour*3600)+(tm.tm_min*60)+tm.tm_sec);
                    
                    printf("orario:%d\n", time_save);
                    
					//Differenza fra l'orario di registrazione salvato nel file e l'orario calcolato
                    if(difftime(timecalc, time_save) >= 10) {
                        //elimino il file dalla directory   
                        remove(path_file); 
                        printf("FILE ELIMINATO: %s\n", path_file);
                    } else {
                        //invio data aggiornat al client
                        sprintf(send_buff, "%d/%d/%d - %d:%d:%d", tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);

                        sendto(s, send_buff, strlen(send_buff)+1, 0, (struct sockaddr *)&si_other, slen);
                    }
                }
            }
        }
        (void) closedir(p); //chiudo la directory
        printf("-------------------------------------------------------------------------------\n");
        sleep(5); //Aspetto 5 sec
    }
    return 0;
}
