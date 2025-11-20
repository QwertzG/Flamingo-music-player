#ifndef ALBUM_H
#define ALBUM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../dataStructures/songll.h"
#include "song.h"

typedef struct album
{
    char name[256];
    char artist[256];
    songll* songs;
}album;

album* aCreate(char* name, char* artist);
void aDestroy(album* album);
song* aFindSongInAlbum(album* album, char* title);
int aAddSong(album* album, song* gaana);
int aRemoveSong(album* album, char* title);
void aPrint(album* album);

#endif