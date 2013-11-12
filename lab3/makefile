OBJS = ../spolks_lib/SignalHandlerNotifier.h  ../spolks_lib/ISignalObserver.h ../spolks_lib/headers.h \
	../spolks_lib/SocketServer.h ../spolks_lib/SocketServer.cpp ../spolks_lib/SocketBase.h \
	../spolks_lib/SocketBase.cpp ../spolks_lib/SocketClient.h ../spolks_lib/SocketClient.cpp \
	../spolks_lib/ClientParameters.h ../spolks_lib/SignalHandlerNotifier.cpp \
	./FileWriter.h ./FileWriter.cpp ./FileReader.h ./FileReader.cpp \
	./SocketFileReceiver.h ./SocketFileReceiver.cpp ./SocketFileSender.h \
	./SocketFileSender.cpp ../spolks_lib/StringToIntConverter.h ./main.cpp

CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

lab3 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./lab3

clean:
	\rm -f *.o *~ lab3
