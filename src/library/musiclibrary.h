#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H
#include <stdio.h>
#include <stdlib.h>
#include "../dataStructures/albumll.h"
#include "../dataStructures/songll.h"
#include "../coreFunctions/song.h"
#include "../coreFunctions/album.h"

typedef struct library
{
    songll* songs;
    albumll* albums;
} library;

library* MLCreate();
void MLDestroy(library* library);
int MLLoadSongs(library* library, char* filepath);
int MLLoadAlbums(library* library, char* filepath);
int MLSaveAlbums(library* library, char* filepath);
song* MLFindSong(library* library, char* title);
void MLListAllSongs(library* library);
int MLSongCount(library* library);
album* MLFindAlbum(library* library, char* title);
int MLAddAlbum(library* library,album* alb);
int MLRemoveAlbum(library* library, char* title);
void MLListAllAlbums(library* library);
int MLAlbumCount(library* library);

#endif