##==================================================================##
 #
 # Makefile for the sequential implementation of QuickSort
 #
 # Frank Blanning <frankgou@ece.auth.gr>
 # AEM: 6698
 # Time-stamp: <2018-10-28>
 #
##==================================================================##

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CC = gcc
endif

ifeq ($(UNAME_S),Darwin)
	CC = gcc-mp-7
endif

CFLAGS = -O3

CMAIN=qsort

all: qsort-main.o qsort-sequential.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)
