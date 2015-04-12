CFLAGS=-Wall -pedantic -g
PROG=wf
SRCS=stringhash.c wf.c
HEADERS=stringhash.h
OBJS=${SRCS:.c=.o}

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJS): $(HEADERS)

clean: objclean
	rm -f $(PROG)

objclean:
	rm -f *.o *.gch

