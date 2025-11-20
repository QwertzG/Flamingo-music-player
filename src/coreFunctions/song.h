#ifndef SONG_H
#define SONG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song
{
    char title[256];
    char artist[256];
    char album[256];
    char filepath[256];
    int length;
}song;

song* sCreate(const char* title, const char* artist, const char* album, const char* filepath, int length);
void sRemove(song* song);
song* sCopy(song* dollar);
void sPrint(song* song);
void sPrintExtra(song* song);

#endif