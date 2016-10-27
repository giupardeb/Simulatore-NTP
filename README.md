# SIMULAZIONE PROTOCOLLO NTP MODELLO CLIENT - SERVER

Il progetto simula il protocollo NTP (Network Time Protocol), utilizzato per sincronizzare gli orologi dei computer 
all'interno di una rete a commutazione di pacchetto.Il progetto utilizza il modello Client – Server basato sul protocollo UDP,
dove un determinato numero di client, effettuando la registrazione al servizio sul server, “riceveranno l’orario corretto”.
In conseguenza di ciò, qualora uno o più client dovessero avere l’orario di sistema errato, dovuto ad un mal funzionamento 
del sistema locale, il server ad intervalli regolari, contatta i client registrati, provvedendo automaticamente 
a sincronizzagli l’orario di sistema con quello corretto presente nel server.

##Funzionamento

il client all’interno si comporta sia come Sender che come Receiver.
Dal “lato client” questo comportamento è importante
per poter contemporaneamente ricevere la data aggiornata
dal server e poter inviare la propria richiesta di
registrazione al server.

###Lato Client
* **Sender:** dopo aver inizializzato e configurato la
socket, invia il proprio indirizzo IP al server per
potersi registrare al servizio, tale comportamento
avviene in modo pseudo-random per poter simulare al
meglio la volontà o meno del client di volersi
registrare al servizio.
* **Receiver:** semplicemente riceve la data aggiornata dal
server.

###Lato Server
* **Receiver:** dopo aver inizializzato e configurato la
socket, si mette in attesa di ricevere le
registrazioni dei client mediante indirizzo IP.
Ricevuto l’indirizzo IP il Receiver crea un file di
testo di tipo “IP.txt”, dove l’IP corrisponde
all’indirizzo del client che ha inviato la
registrazione, se il file esiste già, ciò significa
che il client ha rinnovato la propria registrazione
al servizio e quindi bisognerà aggiornare solo
l’orario di registrazione, altrimenti si crea il file
“IP.txt” inserendo l’orario di registrazione.

* **Sender:** dopo aver inizializzato e configurato alcuni
parametri della socket, entra in un ciclo while in
loop. All’interno di esso si cercheranno tutti i file
di tipo “IP.txt”, da qui si estrae l’indirizzo “IP”
del client da notificare, e successivamente legge
all’interno del file l’orario di registrazione del
client, se è maggiore di 30 secondi, il file viene
eliminato e il client in questione non notificato,
altrimenti invia l’orario aggiornato al client.
