CROSS = arm-linux-gnueabihf-

CC = $(CROSS)gcc

STRIP = $(CROSS)strip 

CFLAGS = -g -O2 -Wall

#include

INC = -I./bsp -I./bsp/wraperror \
	  -I./bsp/wrapsqlite3/ -I./bsp/wrappthread

#lib
LIBS = -L./lib -lsqlite3 -lpthread

#src
SRC = test.c  bsp/wraperror/wraperror.c \
      bsp/wrapsqlite3/wrapsqlite.c \
      bsp/wrappthread/wrappthread.c

#target
TARGET = test

#objs
OBJS = $(SRC:.c=.o)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJS)

install: $(TARGET) clean
	@echo start compile...
	@echo end.

%.o:%.c
	$(CC) $(CFLAGS) $(INC) $(LIBS) -o $@ -c $<



