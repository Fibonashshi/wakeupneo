CC      := cc
CFLAGS  := -Wall -Wextra -std=c99 -pedantic
LDFLAGS := -lncurses
SRC     := src/wake-up-neo.c
BIN     := bin/wake-up-neo
PREFIX  := /usr/local/bin

.PHONY: all clean install uninstall

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

install: $(BIN)
	install -m 755 $(BIN) $(PREFIX)

uninstall:
	rm -f $(PREFIX)/wake-up-neo

clean:
	rm -f $(BIN)
