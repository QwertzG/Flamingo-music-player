#ifndef SONGLL_H
#define SONGLL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../coreFunctions/song.h"

typedef struct sNode
{
    song* song;
    struct sNode* pNext;
}sNode;

typedef struct songll
{
    sNode* head;
    sNode* tail;
    int size;
}songll;

songll* sllCreate();
void sllDestroy(songll* sll);
int sllAddSong(songll* sll, song* gaana);
int sllRemoveSong(songll* sll, char* title);
void sllPrint(songll* sll);
song* sllFind(songll* sll, char* title);

#endif