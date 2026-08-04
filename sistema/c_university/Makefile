CC=gcc
CFLAGS=-Wall -I./src
SRC=src/main.c src/storage_file.c
LIBS=

all: university

university:
	$(CC) $(CFLAGS) -o university $(SRC) $(LIBS)

sqlite: CFLAGS += -DHAVE_SQLITE
sqlite: SRC += src/storage_sqlite.c
sqlite: LIBS += -lsqlite3
sqlite:
	$(CC) $(CFLAGS) -o university $(SRC) $(LIBS)

clean:
	rm -f university
