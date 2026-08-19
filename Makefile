SRC_DIR= ./src
SRCS= $(SRC_DIR)/main.c $(SRC_DIR)/linked_list.c $(SRC_DIR)/address.c

CC= gcc
FLAGS= -Iinclude -Wall -Werror -pedantic 


all: clean build

valgrind:
	$(CC) $(SRCS) $(FLAGS) -g -o addbook 

build:
	$(CC) $(SRCS) $(FLAGS) -o addbook 

clean:
	rm -f addbook