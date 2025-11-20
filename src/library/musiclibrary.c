#include "musiclibrary.h"
#include "../storage/songio.h"
#include "../storage/albumio.h"

library* MLCreate()
{
    library* lib=(library*)malloc(sizeof(library));
    lib->songs=sllCreate();
    lib->albums=allCreate();
    return lib;
}

void MLDestroy(library* library)
{
    if(library==NULL)
    {
        return;
    }
    if(library->albums!=NULL)
    {
        allDestroy(library->albums);
    }
    if(library->songs!=NULL)
    {
        sNode* temp=library->songs->head;
        while(temp!=NULL)
        {
            sNode* temp2=temp->pNext;
            sRemove(temp->song);
            free(temp);
            temp=temp2;
        }
        free(library->songs);
    }
    free(library);
}

int MLLoadSongs(library* library, char* filepath)
{
    if((library==NULL)||(filepath==NULL))
    {
        return -1;
    }
    songll* lodead=sioLoadSongs(filepath);
    if(library->songs!=NULL)
    {
        sllDestroy(library->songs);      
    }
    library->songs=lodead;
    return 0;
}

int MLLoadAlbums(library* library, char* filepath)
{
    if((library==NULL)||(filepath==NULL))
    {
        return -1;
    }
    albumll* lodead=aioLoadAll(filepath,library->songs);
    if(library->albums!=NULL)
    {
        allDestroy(library->albums);
    }
    library->albums=lodead;
    return 0;
}

int MLSaveAlbums(library* library, char* filepath)
{
    if((library==NULL)||(filepath==NULL))
    {
        return -1;
    }
    return aioSaveAll(library->albums,filepath);
}

song* MLFindSong(library* library, char* title)
{
    if((library==NULL)||(title==NULL))
    {
        return NULL;
    }
    return sllFind(library->songs,(char*)title);
}

void MLListAllSongs(library* library)
{
    if((library==NULL)||(library->songs==NULL))
    {
        printf("[ERROR] No songs in library\n");
        return;
    }
    printf("\n========== SONG LIBRARY (%d songs) ==========\n\n", library->songs->size);
    if(library->songs->size==0)
    {
        printf("  (No songs loaded)\n");
    }
    else
    {
        int count=1;
        sNode* temp=library->songs->head;
        while(temp)
        {
            printf("  %d. ", count++);
            sPrint(temp->song);
            temp = temp->pNext;
        }
    }
    printf("\n==============================================\n\n");
}

int MLSongCount(library* library)
{
    if((library==NULL)||(library->songs==NULL))
    {
        return 0;
    }
    return library->songs->size;
}

album* MLFindAlbum(library* library, char* title)
{
    if((library==NULL)||(title==NULL)||(library->albums==NULL))
    {
        return NULL;
    }
    aNode* temp=library->albums->head;
    while(temp!=NULL)
    {
        if(strcmp(temp->album->name,title)==0)
        {
            return temp->album;
        }
        temp = temp->pNext;
    }
    return NULL;
}

int MLAddAlbum(library* library,album* alb)
{
    if((library==NULL)||(alb==NULL))
    {
        return -1;
    }
    return allAddAlbum(library->albums,alb);
}

int MLRemoveAlbum(library* library, char* title)
{
    if((library==NULL)||(title==NULL))
    {
        return -1;
    }
    return allRemoveAlbum(library->albums,(char*)title);
}

void MLListAllAlbums(library* library)
{
    if((library==NULL)||(library->albums==NULL))
    {
        printf("[ERROR] No albums in library\n");
        return;
    } 
    printf("\n========== ALBUM LIBRARY (%d albums) ==========\n\n", library->albums->size);
    if(library->albums->size==0)
    {
        printf("  (No albums created)\n");
    }
    else
    {
        int c=1;
        aNode* temp=library->albums->head;
        while(temp!=NULL)
        {
            printf("  %d. %s by %s (%d songs)\n", c++, temp->album->name, temp->album->artist, temp->album->songs->size);
            temp=temp->pNext;
        }
    }
    printf("\n===============================================\n\n");
}

int MLAlbumCount(library* library)
{
    if((library==NULL)||(library->albums==NULL))
    {
        return 0;
    }
    return library->albums->size;
}