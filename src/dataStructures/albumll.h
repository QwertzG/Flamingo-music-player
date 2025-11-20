#ifndef ALBUMLL_H
#define ALBUMLL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../coreFunctions/album.h"

typedef struct aNode
{
    album* album;
    struct aNode* pNext;
}aNode;

typedef struct albumll
{
    aNode* head;
    aNode* tail;
    int size;
}albumll;

albumll* allCreate();
void allDestroy(albumll* all);
int allAddAlbum(albumll* all, album* album);
int allRemoveAlbum(albumll* all, char* name);
void allPrint(albumll* all);

#endif