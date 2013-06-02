CC=clang
CFLAGS=-g -Wall -Werror -Wpedantic -Iinclude
LD=clang
LDFLAGS=
PROG=pi_lcd_carousel
OBJS=main.o plc_netinfo.o
RM=/bin/rm -f

all : pi_lcd_carousel

$(PROG): $(OBJS) 
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

plc_netinfo.o: net/plc_netinfo.c include/net/plc_netinfo.h
	$(CC) $(CFLAGS) -c net/plc_netinfo.c -o plc_netinfo.o

clean:
	$(RM) $(PROG) $(OBJS)