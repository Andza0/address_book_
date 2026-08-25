CFLAGS := -Wall -Werror -fpic -I../include
SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)
SO := liblinked_list.so

link: $(OBJECTS)
	$(CC) -shared $(OBJECTS) -o $(SO)
.PHONY: link

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJECTS)
	rm $(SO)
.PHONY: clean