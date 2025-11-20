#ifndef ALBUMIO_H
#define ALBUMIO_H
#include "../dataStructures/albumll.h"
#include "../coreFunctions/album.h"

int aioSaveAll(albumll* albumlist, char* filepath);
albumll* aioLoadAll(char* filepath, songll* songlist);
int aioSave(FILE* file, album* album);

#endif