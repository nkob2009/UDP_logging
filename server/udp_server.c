/*
    Simple udp server
*/
#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
 
void ErrorAbort(char *s)
{
    perror(s);
    exit(1);
}

pthread_t	th;
/*
struct thdata {
    char                letter;
    pthread_t           th;
    sem_t               sync;
    sem_t               start;
};
*/

void *udp_listening_thread(void* pthread_data){

    struct sockaddr_in si_me, si_other;
     
    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
     
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        ErrorAbort("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        ErrorAbort("bind");
    }
     
    //keep listening for data
    while(1)
    {
//        printf("Waiting for data...");
        fflush(stdout);
         
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            ErrorAbort("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        //printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        //printf("Data: %s\n" , buf);
        printf("%s" , buf);
         
        //now reply the client with the same data
        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            ErrorAbort("sendto()");
        }
	memset(buf,0,BUFLEN);
    }
 
    close(s);
    return 0;
}


int main(int argc, char** argv){

int	rtn;
pthread_t	th;
//struct thdata       *thdata;

        rtn = pthread_create(&th, NULL, udp_listening_thread, (void *) NULL);
        if (rtn != 0) {
            fprintf(stderr, "pthread_create() #%0d failed.", rtn);
            exit(EXIT_FAILURE);
        }

	printf("*** completed ***\n");

	while(1){
		sleep(1);
	}
}


