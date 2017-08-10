# make file for udp client

CC	= gcc
CXX	= g++

CFLAGS	= -Wall -DSERVER=\""192.168.0.13"\" -DBUFLEN=512 -DPORT=8888

LIBS	= -lpthread

PROGRAM	= udp_c

OBJS	= udp_client.o udp_send_thread.o

all:	$(OBJS)

	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM) $(LIBS)

clean:
	$(RM)	$(OBJS) 
