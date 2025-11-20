#ifndef FILEIO_H
#define FILEIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* fioReadLine(FILE* file, char* buffer, int max_length);
int fioExists(char* filepath);

#endif