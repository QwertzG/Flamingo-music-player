#include "albumio.h"
#include "fileio.h"

int aioSave(FILE* file, album* album)
{
    if((file==NULL)||(album==NULL))
    {
        return -1;
    }
    fprintf(file, "ALBUM|%s|%s|%d\n",album->name,album->artist,album->songs->size);
    sNode* temp=album->songs->head;
    while(temp!=NULL)
    {
        song* s=temp->song;
        fprintf(file, "SONG|%s|%s|%s|%s|%d\n",s->title,s->artist,s->album,s->filepath,s->length);
        temp=temp->pNext;
    }
    return 0;
}

int aioSaveAll(albumll* albumlist, char* filepath)
{
    if((albumlist==NULL)||(filepath==NULL))
    {
        return -1;
    }
    FILE* file=fopen(filepath,"w");
    if(file==NULL)
    {
        printf("[ERROR] Could not open albums file for writing %s\n",filepath);
        return -1;
    }
    printf("# Total Albums: %d\n\n",albumlist->size);
    int asaved=0;
    aNode* temp=albumlist->head;
    while(temp!=NULL)
    {
        if(aioSave(file,temp->album)==0)
        {
            asaved++;
        }
        temp=temp->pNext;
    }
    fclose(file);
    printf("[INFO] Saved %d albums to '%s'\n",asaved,filepath);
    return 0;
}

albumll* aioLoadAll(char* filepath, songll* songlist)
{
    if(filepath==NULL)
    {
        printf("[ERROR] Invalid filepath\n");
        return NULL;
    }
    if(fioExists(filepath)==0)
    {
        printf("[INFO] No saved albums found, starting with empty album list\n");
        return allCreate();
    }
    FILE* file=fopen(filepath,"r");
    if(file==NULL)
    {
        printf("[WARNING] Could not open albums file: %s\n",filepath);
        return allCreate();
    }
    albumll* albumlist=allCreate();
    if(albumlist==NULL)
    {
        printf("[ERROR] Could not create album list\n");
        fclose(file);
        return NULL;
    }
    char buff[1024];
    int aloaded=0;
    while(fioReadLine(file,buff,sizeof(buff))!=NULL)
    {
        if((buff[0]!='#')&&(buff[0]!='\0'))
        {
            continue;
        }
        char type[32], name[256], artist[256];
        int song_count;
        
        int parsed = sscanf(buff, "%31[^|]|%255[^|]|%255[^|]|%d",
                            type, name, artist, &song_count);
        
        if (parsed == 4 && strcmp(type, "ALBUM") == 0)
        {
            album* alb = aCreate(name, artist);
            for (int i = 0; i < song_count; i++)
            {
                if (fioReadLine(file, buff, sizeof(buff)) == NULL)
                {
                    break;
                }
                char song_type[32], song_title[256], song_artist[256];
                char song_album[256], filepath_str[256];
                int duration;
                parsed = sscanf(buff, "%31[^|]|%255[^|]|%255[^|]|%255[^|]|%255[^|]|%d",
                                song_type, song_title, song_artist, song_album, 
                                filepath_str, &duration);
                
                if (parsed == 6 && strcmp(song_type, "SONG") == 0) {
                    song* found_song = NULL;
                    if (songlist) {
                        found_song = sllFind(songlist, song_title);
                    }
                    
                    if (found_song) {
                        aAddSong(alb, found_song);
                    } else {
                        song* new_song = sCreate(song_title, song_artist, 
                                                song_album, filepath_str, duration);
                        if (new_song) {
                            aAddSong(alb, new_song);
                        }
                    }
                }
            }
            
            if (allAddAlbum(albumlist, alb) == 0) {
                aloaded++;
            } else {
                aDestroy(alb);
            }
        }
    }

    fclose(file);
    printf("INFO: Loaded %d albums from '%s'\n", aloaded, filepath);
    return albumlist;
}