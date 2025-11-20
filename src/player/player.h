#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include "../dataStructures/playlistcll.h"
#include "../coreFunctions/song.h"

typedef struct player
{
    pcll* playlist;
    int is_playing;
}player;

player* pyCreate();
void pyDestroy(player* player);
int pyAddSong(player* player, song* s);
int pyRemoveCurrentSong(player* player);
void pyClearPlaylist(player* player);
int pyPlaylistSize(player* player);
song* pyFetchCurrentSong(player* player);
song* pyNext(player* player);
song* pyPrevious(player* player);
void pyPlay(player* player);
void pyPause(player* player);
void pyDisplayPlaylist(player* player);
void pyDisplayNowPlaying(player* player);

#endif