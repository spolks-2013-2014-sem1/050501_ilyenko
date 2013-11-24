OBJS = ../spolks_lib/SignalHandlerNotifier.h  ../spolks_lib/ISignalObserver.h ../spolks_lib/headers.h \
	../spolks_lib/SocketServer.h ../spolks_lib/SocketServer.cpp ../spolks_lib/SocketBase.h \
	../spolks_lib/SocketBase.cpp ../spolks_lib/SocketClient.h ../spolks_lib/SocketClient.cpp \
	../spolks_lib/ClientParameters.h ../spolks_lib/SignalHandlerNotifier.cpp \
	../lab3/FileWriter.h ../lab3/FileWriter.cpp ../lab3/FileReader.h ../lab3/FileReader.cpp \
	../lab3/SocketFileReceiver.h ../lab3/SocketFileReceiver.cpp ../lab3/SocketFileSender.h \
	../lab3/SocketFileSender.cpp ../spolks_lib/StringToIntConverter.h ./main.cpp \
	./FileSenderWithUrgentData.h ./FileSenderWithUrgentData.cpp \
	./FileReceiverWithUrgentData.h ./FileReceiverWithUrgentData.cpp

CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

lab4 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./lab4

clean:
	\rm -f *.o *~ lab4