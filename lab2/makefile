OBJS = ./main.cpp ./SocketServer.h ./SocketServer.cpp ./headers.h \
	./SignalHandlerObserver.h ./SignalHandlerObserver.cpp ./IHandlerSubscribable.h
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

lab2 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o lab2

clean:
	\rm -f *.o *~ lab2