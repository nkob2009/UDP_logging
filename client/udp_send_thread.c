#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <pthread.h>

//#define SERVER "127.0.0.1"
//#define BUFLEN 512  //Max length of buffer
//#define PORT 8888   //The port on which to send data

void error_abort(char *s)
{
    perror(s);
    exit(1);
}

void *udp_send_thread(void* pthread_data)
{
    struct sockaddr_in si_other;
    int s, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    int index;

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        error_abort("socket");
    }
 
//    memset((char *) &si_other, 0, sizeof(si_other));
        //inet_aton("127.0.0.1",&si_other);
        inet_aton("192.168.0.13",&si_other);
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    index = 0;
    while(1)
    {
//        printf("Enter message : ");
//        gets(message);
	sprintf(message,"%d",index);
//	strcat(message,"\n");
         
        //send the message
        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            error_abort("sendto()");
        }
         
        // buffer clear
        memset(buf,'\0', BUFLEN);
        // receive data 
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            error_abort("recvfrom()");
        }
         
        puts(buf);

	sleep(1);
	index++;
    }

    close(s);
    return 0;
}

