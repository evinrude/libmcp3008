SOURCES:= client.c
CC:= gcc
CC_OPTS:= -lmcp3008 -Wall -L../lib -I../lib

.PHONY: client

default: all

all: client

client:
	$(CC) $(SOURCES) $(CC_OPTS) -o client
	
clean:
	rm -fv client	
