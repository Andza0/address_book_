OBJECTS = $(wildcard ./src/*.o)

all: LIB SRC addbook

addbook: $(OBJECTS) 
	$(CC) -L./lib \
	-Wl,-rpath,'$$ORIGIN/lib' \
	$(OBJECTS) -o addbook -llinked_list -lncurses
.PHONY: addbook

SRC:
	$(MAKE) -C ./src
.PHONY: SRC

LIB:
	$(MAKE) -C ./lib
.PHONY: LIB

clean:
	$(MAKE) clean -C ./src
	$(MAKE) clean -C ./lib
.PHONY: clean