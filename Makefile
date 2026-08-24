SRC_DIR := ./src
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SRCS:.c=.o)

CC := gcc
CFLAGS := -Iinclude -Wall -Werror -pedantic
LDFLAGS := -lncursesw
VALGRIND_FLAGS := -g

#$(info OBJECTS = [$(OBJECTS)])

all: clean addbook

addbook: $(OBJECTS)
	$(CC) $(OBJECTS)  -o addbook $(LDFLAGS)

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f addbook

valgrind:
	$(CC) $(CFLAGS) $(SRCS) -o addbook $(LDFLAGS)