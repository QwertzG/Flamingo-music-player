#include "cli.h"

cli* cliCreate()
{
    cli* cl=(cli*)malloc(sizeof(cli));
    cl->library=MLCreate();
    cl->player=pyCreate();
    cl->running=0;
    return cl;
}

void cliDestroy(cli* cli)
{
    if(cli==NULL)
    {
        return;
    }
    if(cli->library)
    {
        MLDestroy(cli->library);
    }
    if(cli->player)
    {
        pyDestroy(cli->player);
    }
    free(cli);
}

int cliInitialise(cli* cli)
{
    if(cli==NULL)
    {
        return -1;
    }
    if(logInitialise("data/commandHistory.txt")!=0)
    {
        printf("[WARNING] Could not initialist logger\n");
    }
    printf("Loading songs from database...\n");
    if(MLLoadAlbums(cli->library,"data/songs.txt")!=0)
    {
        printf("[ERROR] Could not load songs\n");
        return -1;
    }
    printf("Loading saved albums...\n");
    MLLoadAlbums(cli->library,"data/albums.txt");
    printf("\n");
    return 0;
}

void cliRun(cli* cli)
{
    if(cli==NULL)
    {
        return;
    }
    cli->running=1;
    char input[1024];
    while(cli->running)
    {
        cliDisplayPrompt();
        if(fgets(input,sizeof(input),stdin)==NULL)
        {
            break;
        }
        size_t len=strlen(input);
        if((len>0)&&(input[len-1]=='\n'))
        {
            input[len-1]='\0';
        }
        cliHandleCommand(cli,input);
    }
}

void cliDisplayWelcome()
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║                                                ║\n");
    printf("║                 Flamingo                       ║\n");
    printf("║        A Command-Line Music Player             ║\n");
    printf("║                                                ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Type 'help' for available commands.\n");
    printf("Type 'exit' to quit.\n\n");
}

void cliDisplayHelp()
{
    printf("\n========== AVAILABLE COMMANDS ==========\n\n");    
    printf("LIBRARY COMMANDS:\n");
    printf("  list songs              - List all songs in library\n");
    printf("  list albums             - List all albums\n");
    printf("  view album <name>       - View songs in an album\n");
    printf("\n");
    printf("ALBUM MANAGEMENT:\n");
    printf("  create album <name> <artist>  - Create a new album\n");
    printf("  delete album <name>           - Delete an album\n");
    printf("  add to album <album> <song>   - Add song to album\n");
    printf("  remove from album <album> <song> - Remove song from album\n");
    printf("\n");
    printf("PLAYER COMMANDS:\n");
    printf("  play                    - Play current playlist\n");
    printf("  pause                   - Pause playback\n");
    printf("  next                    - Play next song\n");
    printf("  prev                    - Play previous song\n");
    printf("  now playing             - Show current song\n");
    printf("\n");
    printf("PLAYLIST COMMANDS:\n");
    printf("  show playlist           - Display current playlist\n");
    printf("  add song <title>        - Add song to playlist\n");
    printf("  add album <name>        - Add all songs from album to playlist\n");
    printf("  remove current          - Remove current song from playlist\n");
    printf("  clear playlist          - Clear entire playlist\n");
    printf("\n");
    printf("OTHER COMMANDS:\n");
    printf("  history                 - Show command history\n");
    printf("  help                    - Show this help message\n");
    printf("  exit                    - Exit application\n");
    printf("\n========================================\n\n");
}

void cliDisplayPrompt()
{
    printf("flamingo> ");
    fflush(stdout);
}

static char* trim(char* str)
{
    while(isspace(*str))
    {
        str++;
    }
    char* end=str+strlen(str)-1;
    while((end>str)&&(isspace(*end)))
    {
        end--;
    }
    *(end+1)='\0';
    return str;
}

void cliHandleCommand(cli* cli,char* command)
{
    if((cli==NULL)||(command==NULL))
    {
        return;
    }
    char cmdcopy[1024];
    strncpy(cmdcopy,command,1023);
    cmdcopy[1023]='\0';
    char* trimmed=trim(cmdcopy);
    if(strlen(trimmed)==0)
    {
        return;
    }
    logCommand(trimmed);
    if((strcmp(trimmed,"exit")==0)||(strcmp(trimmed,"quit"))==0)
    {
        printf("Saving albums...\n");
        MLSaveAlbums(cli->library,"data/albums.txt");
        printf("Goodbye!\n\n");
        cli->running=0;
    }
    else if (strcmp(trimmed, "help") == 0)
    {
        cliDisplayHelp();
    }
    else if (strcmp(trimmed, "list songs") == 0)
    {
        MLListAllSongs(cli->library);
    }
    else if (strcmp(trimmed, "list albums") == 0)
    {
        MLListAllAlbums(cli->library);
    }
    else if (strncmp(trimmed, "view album ", 11) == 0)
    {
        char* album_name = trimmed + 11;
        album* alb = MLFindAlbum(cli->library, album_name);
        if (alb)
        {
            aPrint(alb);
            printf("Songs in album:\n");
            sllPrint(alb->songs);
        }
        else
        {
            printf("Album '%s' not found.\n", album_name);
        }
    }
    else if (strncmp(trimmed, "create album ", 13) == 0)
    {
        char* args = trimmed + 13;
        char name[256], artist[256];
        if (sscanf(args, "%255[^,],%255[^\n]", name, artist) == 2)
        {
            char* trimmed_name = trim(name);
            char* trimmed_artist = trim(artist);
            
            album* alb = aCreate(trimmed_name, trimmed_artist);
            if (alb)
            {
                if (MLAddAlbum(cli->library, alb) == 0)
                {
                    printf("Album '%s' created successfully.\n", trimmed_name);
                }
                else
                {
                    printf("Failed to add album.\n");
                    aDestroy(alb);
                }
            }
        }
        else
        {
            printf("Usage: create album <name>, <artist>\n");
        }
    }
    else if (strncmp(trimmed, "delete album ", 13) == 0)
    {
        char* album_name = trimmed + 13;
        if (MLRemoveAlbum(cli->library, album_name) == 0)
        {
            printf("Album '%s' deleted.\n", album_name);
        }
        else
        {
            printf("Album '%s' not found.\n", album_name);
        }
    }
    else if (strncmp(trimmed, "add to album ", 13) == 0)
    {
        char* args = trimmed + 13;
        char album_name[256], song_title[256];
        if (sscanf(args, "%255[^,],%255[^\n]", album_name, song_title) == 2)
        {
            char* trimmed_album = trim(album_name);
            char* trimmed_song = trim(song_title);
            album* alb = MLFindAlbum(cli->library, trimmed_album);
            song* s = MLFindSong(cli->library, trimmed_song);
            
            if (!alb)
            {
                printf("Album '%s' not found.\n", trimmed_album);
            }
            else if (!s)
            {
                printf("Song '%s' not found.\n", trimmed_song);
            }
            else
            {
                if (aAddSong(alb, s) == 0)
                {
                    printf("Added '%s' to album '%s'.\n", trimmed_song, trimmed_album);
                }
                else
                {
                    printf("Failed to add song (may already exist in album).\n");
                }
            }
        }
        else
        {
            printf("Usage: add to album <album_name>, <song_title>\n");
        }
    }
    else if (strncmp(trimmed, "remove from album ", 18) == 0)
    {
        char* args = trimmed + 18;
        char album_name[256], song_title[256];
        if (sscanf(args, "%255[^,],%255[^\n]", album_name, song_title) == 2)
        {
            char* trimmed_album = trim(album_name);
            char* trimmed_song = trim(song_title);    
            album* alb = MLFindAlbum(cli->library, trimmed_album);
            song* s = MLFindSong(cli->library, trimmed_song);
            if (!alb)
            {
                printf("Album '%s' not found.\n", trimmed_album);
            }
            else if (!s)
            {
                printf("Song '%s' not found.\n", trimmed_song);
            }
            else
            {
                if (sllRemoveSong(alb->songs, trimmed_song) == 0)
                {
                    alb->songs->size--;
                    printf("Removed '%s' from album '%s'.\n", trimmed_song, trimmed_album);
                }
                else
                {
                    printf("Song not found in album.\n");
                }
            }
        }
        else
        {
            printf("Usage: remove from album <album_name>, <song_title>\n");
        }
    }
    else if (strcmp(trimmed, "show playlist") == 0)
    {
        pyDisplayPlaylist(cli->player);
    }
    else if (strncmp(trimmed, "add song ", 9) == 0)
    {
        char* song_title = trimmed + 9;
        song* s = MLFindSong(cli->library, song_title);
        if (s)
        {
            if (pyAddSong(cli->player, s) == 0)
            {
                printf("Added '%s' to playlist.\n", song_title);
            }
            else
            {
                printf("Failed to add song to playlist.\n");
            }
        }
        else
        {
            printf("Song '%s' not found.\n", song_title);
        }
    }
    else if (strncmp(trimmed, "add album ", 10) == 0)
    {
        char* album_name = trimmed + 10;
        album* alb = MLFindAlbum(cli->library, album_name);
        if (alb)
        {
            int added = 0;
            sNode* current = alb->songs->head;
            while (current) {
                if (pyAddSong(cli->player, current->song) == 0)
                {
                    added++;
                }
                current = current->pNext;
            }
            printf("Added %d songs from album '%s' to playlist.\n", added, album_name);
        }
        else
        {
            printf("Album '%s' not found.\n", album_name);
        }
    }
    else if (strcmp(trimmed, "remove current") == 0)
    {
        if (pyRemoveCurrentSong(cli->player) == 0)
        {
            printf("Current song removed from playlist.\n");
        }
        else
        {
            printf("No song to remove.\n");
        }
    }
    else if (strcmp(trimmed, "clear playlist") == 0)
    {
        pyClearPlaylist(cli->player);
    }
    else if (strcmp(trimmed, "play") == 0)
    {
        pyPlay(cli->player);
    }
    else if (strcmp(trimmed, "pause") == 0)
    {
        pyPause(cli->player);
    }
    else if (strcmp(trimmed, "next") == 0)
    {
        if (!pyNext(cli->player)) {
            printf("No next song (playlist empty).\n");
        }
    }
    else if (strcmp(trimmed, "prev") == 0 || strcmp(trimmed, "previous") == 0)
    {
        if (!pyPrevious(cli->player))
        {
            printf("No previous song (playlist empty).\n");
        }
    }
    else if (strcmp(trimmed, "now playing") == 0)
    {
        pyDisplayNowPlaying(cli->player);
    }
    else if (strcmp(trimmed, "history") == 0)
    {
        logDisplayHistory();
    }
    else
    {
        printf("Unknown command: '%s'. Type 'help' for available commands.\n", trimmed);
    }
}