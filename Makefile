CFILES := set1.c util.c cipher.c frequency.c
PROG := set1
CFLAGS := -Wall -Wextra -g -std=c99
LDFLAGS := -lm

CC := gcc

OBJFILES := $(CFILES:.c=.o)

$(PROG) : $(OBJFILES)
	$(LINK.o) -o $@ $^ $(LDFLAGS)

clean :
	rm -f $(PROG) $(OBJFILES)

-include $(DEPFILES)
