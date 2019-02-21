TARGET=all
CC=gcc
CFLAGS=-Wall -g
LIBS=

ELF = $(patsubst %.c, %, $(wildcard */*.c) )
SRC = $(wildcard */*.c)
HEADERS = $(wildcard */*.h)

.PHONY: clean
.DEFAULT: $(TARGET)

$(TARGET): $(ELF) $(HEADERS)


%: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@
	mv $@ .

uninstall: clean

clean:
	rm -f udp*
	rm -f tcp*
