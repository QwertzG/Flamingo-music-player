#include "fileio.h"

char* fioReadLine(FILE* file, char* buffer, int length) {
    if((file==NULL)||(buffer==NULL))
    {
        return NULL;
    }
    if (fgets(buffer, length, file)==NULL)
    {
        return NULL;
    }
    size_t len = strlen(buffer);
    if ((len>0)&&(buffer[len - 1]=='\n'))
    {
        buffer[len - 1]='\0';
        len--;
    }
    return buffer;
}

int fioExists(char* filepath)
{
    if(filepath==NULL)
    {
        return 0;
    }
    FILE* file=fopen(filepath, "r");
    if(file!=NULL)
    {
        fclose(file);
        return 1;
    }
    return 0;
}