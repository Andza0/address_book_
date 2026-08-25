CFLAGS := -Wall -Werror -I../include
SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

all: $(OBJECTS)
.PHONY: all

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJECTS)
.PHONY: clean