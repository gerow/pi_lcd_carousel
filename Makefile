CC=clang
CFLAGS=-g -Wall -Werror -Wpedantic -Iinclude
LD=clang
LDFLAGS=
PROG=pi_lcd_carousel
OBJS=main.o net/plc_netinfo.o
RM=/bin/rm -f

all : pi_lcd_carousel

$(PROG): $(OBJS) 
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(PROG) $(OBJS)