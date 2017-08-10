# make file for udp client

CC	= gcc
CXX	= g++

CFLAGS	= -Wall 

LIBS	= -lpthread

PROGRAM	= udp_s

OBJS	= udp_server.o 

all:	$(OBJS)

	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM) $(LIBS)

clean:
	$(RM)	$(OBJS) 
