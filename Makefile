# Makefile for HW3 Web Report, ecs36b, f2020
#

CC = g++ -std=c++14
CFLAGS = -g -g -I/opt/homebrew/include

# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

# CORE_INCS =	Core.h Transaction.h Person.h
# CORE_OBJS =	Core.o Transaction.o Person.o
# SHADOW_INCS = Shadow_Flight.h Shadow_Person.h
# SHADOW_OBJS = Shadow_Flight.o Shadow_Person.o 

LDFLAGS = -L/opt/homebrew/lib -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

# rules.
all: 	poclient poserver

#
#

poclient.h:		ecs36b_po.json
	jsonrpcstub ecs36b_po.json --cpp-server=poServer --cpp-client=poClient

poserver.h:		ecs36b_po.json
	jsonrpcstub ecs36b_po.json --cpp-server=poServer --cpp-client=poClient

poclient.o:		poclient.h poclient.cpp
	$(CC) -c $(CFLAGS) poclient.cpp

poserver.o:		poserver.h poserver.cpp
	$(CC) -c $(CFLAGS) poserver.cpp

GPS.o:		GPS.cpp GPS.h
	$(CC) -c $(CFLAGS) GPS.cpp

Shadow_GPS.o:	Shadow_GPS.cpp Shadow_GPS.h GPS.h Labeled_GPS.h
	$(CC) -c $(CFLAGS) Shadow_GPS.cpp

Labeled_GPS.o:	Labeled_GPS.cpp Labeled_GPS.h GPS.h
	$(CC) -c $(CFLAGS) Labeled_GPS.cpp

poclient:	poclient.o Shadow_GPS.o Labeled_GPS.o GPS.o
	$(CC) -o poclient poclient.o Shadow_GPS.o Labeled_GPS.o GPS.o $(LDFLAGS)

poserver:	poserver.o Shadow_GPS.o Labeled_GPS.o GPS.o
	$(CC) -o poserver poserver.o Shadow_GPS.o Labeled_GPS.o GPS.o $(LDFLAGS)

clean:
	rm -f *.o *~ core poclient poserver poclient.h poserver.h
