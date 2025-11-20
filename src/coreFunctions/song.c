#include "song.h"

song* sCreate(const char* title, const char* artist, const char* album, const char* filepath, int length)
{
    song* newSong = (song*)malloc(sizeof(song));
    newSong->length=length;
    strncpy(newSong->title,title,255);
    newSong->title[255]='\0';
    strncpy(newSong->artist,artist,255);
    newSong->artist[255]='\0';
    strncpy(newSong->album,album,255);
    newSong->album[255]='\0';
    strncpy(newSong->filepath,filepath,255);
    newSong->filepath[255]='\0';
    return newSong;
}

void sRemove(song* song)
{
    if(song!=NULL)
    {
        free(song);
    }
}

song* sCopy(song* dollar)
{
    if(dollar==NULL)
    {
        return NULL;
    }
    song* hi = (song*)malloc(sizeof(song));
    strcpy(hi->title,dollar->title);
    strcpy(hi->artist,dollar->artist);
    strcpy(hi->album,dollar->album);
    strcpy(hi->filepath,dollar->filepath);
    hi->length=dollar->length;
    return hi;
}

void sPrint(song* song)
{
    if(song==NULL)
    {
        return;
    }
    printf("%s by %s from: %s, (%d:%d)\n",song->title,song->artist,song->album,song->length/60,song->length%60);
}

void sPrintExtra(song* song)
{
    if(song==NULL)
    {
        return;
    }
    printf("=====Song details=====\n");
    printf("Title     : %s\n",song->title);
    printf("Arist     : %s\n",song->artist);
    printf("Album     : %s\n",song->album);
    printf("Length    : %d:%d\n",song->length/60,song->length%60);
    printf("Path      : %s\n",song->filepath);
    printf("======================\n");
}