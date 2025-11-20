CC = gcc
CFLAGS = -I -g -Wall
SRC = main.c \
          src/coreFunctions/song.c \
          src/coreFunctions/album.c \
          src/dataStructures/songll.c \
          src/dataStructures/albumll.c \
          src/dataStructures/playlistcll.c \
          src/storage/fileio.c \
          src/storage/songio.c \
          src/storage/albumio.c \
          src/storage/cmdlog.c \
          src/library/musiclibrary.c \
          src/player/player.c \
          src/cli/cli.c
OUT = main

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
