SOURCES  = *.c
INCLUDES = *.h
OBJECTS = SCREEN.o

CFLAGS = -Wall -Wextra -Wno-error
LDLIBS = -lncurses

all: SCREEN

SCREEN: $(OBJECTS)
	gcc $(SOURCES) -o screen $(CFLAGS) $(LDLIBS) -D_GNU_SOURCE

.PHONY: clean
clean:
	rm -rf $(OBJECTS)