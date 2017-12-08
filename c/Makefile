.SUFFIXES:

CC = gcc
CFLAGS = -Og -g -Wall -Werror
LDFLAGS = -lm -lcurl

SRCS=$(wildcard *.c)
SRCS:=$(filter-out pattern.c, $(SRCS))
SRCS:=$(filter-out euler.c, $(SRCS))
SRCS:=$(filter-out eulertest.c, $(SRCS))

OBJS=$(SRCS:.c=.o)
EXES=$(OBJS:.o=)

.PHONY: all clean
.PRECIOUS: euler.o

all: $(EXES)
clean:
	-rm -f *.o $(EXES) eulertest

euler.o: euler.c euler.h
	$(CC) -c -o $@ $< $(CFLAGS)
%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)

eulertest: eulertest.o
%: euler.o %.o euler.h
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
