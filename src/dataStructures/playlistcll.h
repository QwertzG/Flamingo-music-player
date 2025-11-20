#ifndef PLAYLISTCLL_H
#define PLAYLISTCLL_H
#include <stdio.h>
#include <stdlib.h>
#include "../coreFunctions/song.h"

typedef struct pNode
{
    song* song;
    struct pNode* pNext;
}pNode;

typedef struct playlistcll
{
    pNode* current;
    int size;
}pcll;

pcll* pcllCreate();
void pcllDestroy(pcll* pcll);
int pcllAddSong(pcll* pcll, song* gaana);
song* pcllRemoveCurrentSong(pcll* pcll);
void pcllClear(pcll* pcll);
void pcllPrint(pcll* pcll);
song* pcllFetchCurrentSong(pcll* pcll);
song* pcllNextSong(pcll* pcll);
song* pcllPreviousSong(pcll* pcll);

#endif