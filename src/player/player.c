#include "player.h"

player* pyCreate()
{
    player* play=(player*)malloc(sizeof(player));
    play->playlist=pcllCreate();
    play->is_playing=0;
    return play;
}

void pyDestroy(player* player)
{
    if(player==NULL)
    {
        return;
    }
    if(player->playlist!=NULL)
    {
        pcllDestroy(player->playlist);
    }
    free(player);
}

int pyAddSong(player* player, song* s)
{
   if((player==NULL)||(s==NULL))
   {
    return -1;
   }
   return pcllAddSong(player->playlist,s);
}

int pyRemoveCurrentSong(player* player)
{
    if((player==NULL)||(player->playlist==NULL))
    {
        return -1;
    }
    song* removed= pcllRemoveCurrentSong(player->playlist);
    if(removed==NULL)
    {
        return -1;
    }
    printf("Removed: ");
    sPrint(removed);
    return 0;
}

void pyClearPlaylist(player* player)
{
    if((player==NULL)||(player->playlist==NULL))
    {
        return;
    }
    pcllClear(player->playlist);
    player->is_playing=0;
    printf("Playlist cleared.\n");
}

int pyPlaylistSize(player* player)
{
    if((player==NULL)||(player->playlist==NULL))
    {
        return 0;
    }
    return player->playlist->size;
}

song* pyFetchCurrentSong(player* player)
{
    if((player==NULL)||(player->playlist==NULL)||(player->playlist->current==NULL))
    {
        return NULL;
    }
    return player->playlist->current->song;
}

song* pyNext(player* player)
{
    if((player==NULL)||(player->playlist==NULL))
    {
        return NULL;
    }
    song* nextSong=pcllNextSong(player->playlist);
    if(nextSong!=NULL)
    {
        printf("Going next: ");
        sPrint(nextSong);
    }
    return nextSong;
}

song* pyPrevious(player* player)
{
    if((player==NULL)||(player->playlist==NULL))
    {
        return NULL;
    }
    song* prevSong=pcllPreviousSong(player->playlist);
    if(prevSong!=NULL)
    {
        printf("Going back: ");
        sPrint(prevSong);
    }
    return prevSong;
}

void pyPlay(player* player)
{
    if(player==NULL)
    {
        return;
    }
    if(player->playlist->size==0)
    {
        printf("Playlist is empty. Add songs first\n");
        return;
    }
    player->is_playing=1;
    printf("Currently playing: ");
    song* current=pyFetchCurrentSong(player);
    if(current!=NULL)
    {
        sPrint(current);
    }
}

void pyPause(player* player)
{
    if(player==NULL)
    {
        return;
    }
    player->is_playing=0;
    printf("Paused\n");
}

void pyDisplayPlaylist(player* player)
{
    if((player==NULL)||(player->playlist==NULL))
    {
        printf("No playlist\n");
        return;
    }
    printf("\n========== CURRENT PLAYLIST (%d songs) ==========\n\n", player->playlist->size);
    if(player->playlist->size==0)
    {
        printf("  (Playlist is empty)\n");
    }
    else
    {
        pcllPrint(player->playlist);
    }
    printf("\n=================================================\n\n");
}

void pyDisplayNowPlaying(player* player)
{
    if((player==NULL)||(player->playlist==NULL)||(player->playlist->current==NULL))
    {
        printf("\nNo song currently playing\n\n");
        return;
    }
    printf("\n========== NOW PLAYING ==========\n");
    if(player->is_playing!=0)
    {
        printf("Status: Playing\n");
    }
    else
    {
        printf("Status: Paused\n");
    }
    printf("\n");
    sPrintExtra(player->playlist->current->song);   
    printf("=================================\n\n");
}