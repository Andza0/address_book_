SRC_DIR := ./src
SRCS := $(SRC/DIR)/$(wildcard *.c)
OBJECTS := $(SRCS:.c=.o)

CC := gcc
CFLAGS := -Iinclude -Wall -Werror -pedantic -lncursesw
VALGRIND_FLAGS := -g


all: clean addbook

addbook: $(OBJECTS)
	$(CC) $(OBJECTS) $ -o addbook 

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm -f addbook

valgrind:
