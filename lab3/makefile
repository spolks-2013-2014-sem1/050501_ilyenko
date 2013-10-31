OBJS = ./SignalHandlerNotifier.h  ./ISignalObserver.h ./headers.h \
	./SocketServer.h ./SocketServer.cpp ./SocketBase.h \
	./SocketBase.cpp ./SocketClient.h ./SocketClient.cpp \
	./ClientParameters.h ./SignalHandlerNotifier.cpp  ./main.cpp 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

lab3 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./lab3

clean:
	\rm -f *.o *~ lab3
