/*
    Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <pthread.h>

void* udp_send_thread(void* pdata);
 
int main(int argc, char** argv){

int     rtn;
pthread_t       th;
//struct thdata       *thdata;

        rtn = pthread_create(&th, NULL, udp_send_thread, (void *) NULL);
        if (rtn != 0) {
            fprintf(stderr, "pthread_create() #%0d failed.", rtn);
            exit(EXIT_FAILURE);
        }

        printf("*** completed ***\n");

        while(1){
                sleep(1);
        }

	return rtn;
}


