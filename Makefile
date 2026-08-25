SRC_DIR := ./src
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SRCS:.c=.o)

CFLAGS := -I./include -Wall -Werror -pedantic -g
LDFLAGS := -lncursesw

all: clean addbook
.PHONY: all

addbook: $(OBJECTS)
	$(CC) $(OBJECTS) -o addbook $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f addbook
.PHONY: clean