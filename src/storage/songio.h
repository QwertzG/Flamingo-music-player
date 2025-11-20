#ifndef SONGIO_H
#define SONGIO_H

#include "../dataStructures/songll.h"
#include "../coreFunctions/song.h"

songll* sioLoadSongs(char* filepath);
song* sioParseOneLine(char* line);
int sioCountSongs(char* filepath);

#endif