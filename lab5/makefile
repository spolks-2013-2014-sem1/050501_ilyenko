OBJS = ../spolks_lib/ISignalObserver.h ../spolks_lib/headers.h \
	../spolks_lib/SocketServer.cpp  \
	../spolks_lib/SocketBase.cpp  ../spolks_lib/SocketClient.cpp \
	../spolks_lib/ClientParameters.h ../spolks_lib/SignalHandlerNotifier.cpp \
	../lab3/FileWriter.cpp  ../lab3/FileReader.cpp \
	../lab3/SocketFileReceiver.cpp  \
	../lab3/SocketFileSender.cpp ../spolks_lib/StringToIntConverter.h ./main.cpp \

CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

lab5 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./lab5

clean:
	\rm -f *.o *~ lab5