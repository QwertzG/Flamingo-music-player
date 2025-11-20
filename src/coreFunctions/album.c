#include "album.h"

album* aCreate(char* name, char* artist)
{
    album* newAlbum=(album*)malloc(sizeof(album));
    strncpy(newAlbum->name,name,255);
    strncpy(newAlbum->artist,artist,255);
    newAlbum->name[255]='\0';
    newAlbum->artist[255]='\0';
    newAlbum->songs=sllCreate();
    return newAlbum;
}

void aDestroy(album* album)
{
    if(album==NULL)
    {
        return;
    }
    if(album->songs!=NULL)
    {
        sllDestroy(album->songs);
    }
}

song* aFindSongInAlbum(album* album, char* title)
{
    if((album==NULL)||(title==NULL))
    {
        return NULL;
    }
    return sllFind(album->songs,title);
}

int aAddSong(album* album, song* gaana)
{
    if((album==NULL)||(gaana==NULL))
    {
        return -1;
    }
    if(aFindSongInAlbum(album,gaana->title)!=NULL)
    {
        return -1;
    }
    return sllAddSong(album->songs,gaana);
}

int aRemoveSong(album* album, char* title)
{
    if((album==NULL)||(title==NULL))
    {
        return -1;
    }
    return sllRemoveSong(album->songs,title);
}

void aPrint(album* album)
{
    if(album==NULL)
    {
        return;
    }
    printf("\n—————— Album Details —————\n");
    printf("Name    : %s\n",album->name);
    printf("Artist  : %s\n",album->artist);
    printf("Songs   : %d\n",album->songs->size);
    printf("—————————————————————————————\n\n");
}