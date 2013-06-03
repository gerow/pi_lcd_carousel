CC=clang
CFLAGS=-g -Wall -Werror -Iinclude
LD=clang
LDFLAGS=
RM=/bin/rm -f
SRCS=$(shell find -name '*.c' | tr '\n' ' ')
OBJS=$(shell find -name '*.c' | sed -e 's/\.c/\.o/' | tr '\n' ' ')

PROG=pi_lcd_carousel

all : $(PROG)

$(PROG): $(OBJS) 
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(PROG) $(OBJS)
