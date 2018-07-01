.SUFFIXES:

SRCS=$(wildcard *.cs)
SRCS:=$(filter-out pattern.cs, $(SRCS))
SRCS:=$(filter-out euler.cs, $(SRCS))

EXES=$(SRCS:.cs=.exe)

.PHONY: all clean

all: $(EXES)
clean:
	-rm -f $(EXES)

%.exe : %.cs euler.cs
	csc $^
	chmod +x $@
