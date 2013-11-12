OBJS = ../spolks_lib/SocketBase.h ../spolks_lib/SocketBase.cpp ../spolks_lib/SocketServer.h ../spolks_lib/SocketServer.cpp \
    ./../spolks_lib/headers.h ../spolks_lib/SignalHandlerNotifier.h \
    ../spolks_lib/SignalHandlerNotifier.cpp \
    ./SocketEchoServer.h ./SocketEchoServer.cpp ./main.cpp 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

lab2 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o lab2

clean:
	\rm -f *.o *~ lab2