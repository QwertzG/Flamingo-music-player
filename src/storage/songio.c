#include "songio.h"
#include "fileio.h"
#include <ctype.h>

song* sioParseOneLine(char* line)
{
    // format: Title|Artist|Album|Filepath|length
    if ((line==NULL)||(line[0]=='#')||(line[0]=='\0'))
    {
        return NULL;
    }
    while(isspace(*line))
    {
        line++;
    }
    if ((*line == '\0')||(*line == '#'))
    {
        return NULL;
    }

    char title[256], artist[256], album[256], filepath[256];
    int length;
    sscanf(line, "%255[^|]|%255[^|]|%255[^|]|%255[^|]|%d",title, artist, album, filepath, &length);

    return sCreate(title, artist, album, filepath, length);
}

songll* sioLoadSongs(char* filepath)
{
    if(filepath==NULL)
    {
        return NULL;
    }
    FILE* file = fopen(filepath, "r");
    songll* sll = sllCreate();
    char buff[1024];
    int lineno=0,songsloaded=0;
    while(fioReadLine(file,buff,sizeof(buff))!=NULL)
    {
        lineno++;
        char temp[1024];
        strncpy(temp,buff,sizeof(temp)-1);
        temp[sizeof(temp)-1]='\0';
        song* newSong=sioParseOneLine(temp);
        if(newSong!=NULL)
        {
            if(sllAddSong(sll,newSong)==0)
            {
                songsloaded++;
            }
            else
            {
                printf("[WARNING] Failed to add song at line %d\n",lineno);
                sRemove(newSong);
            }
        }
    }
    fclose(file);
    printf("[INFO] %d songs loaded from %s\n", songsloaded,filepath);
    return sll;
}

int sioCountSongs(char* filepath)
{
    if(filepath==NULL)
    {
        return 0;
    }
    FILE* file=fopen(filepath,"r");
    char buff[1024];
    int count=0;
    while(fioReadLine(file,buff,sizeof(buff))!=NULL)
    {
        char* temp=buff;
        while(isspace(*temp))
        {
            temp++;
        }
    }
    return count;
}