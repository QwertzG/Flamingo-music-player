#include "albumll.h"

albumll* allCreate()
{
    albumll* newLL = (albumll*)malloc(sizeof(albumll));
    newLL->head=NULL;
    newLL->tail=NULL;
    newLL->size=0;
    return newLL;
}

void allDestroy(albumll* all)
{
    if(all==NULL)
    {
        return;
    }
    aNode* temp = all->head;
    while (temp!=NULL)
    {
        aNode* temp2 = temp->pNext;
        aDestroy(temp->album);
        free(temp);
        temp=temp2;
    }
    all->head=NULL;
    all->size=0;
    all->tail=NULL;
    free(all);
}

int allAddAlbum(albumll* all, album* album)
{
    if((all==NULL)||(album==NULL))
    {
        return -1;
    }
    aNode* newNode = (aNode*)malloc(sizeof(aNode));
    newNode->album=album;
    newNode->pNext=NULL;
    if(all->tail==NULL)
    {
        all->head=newNode;
        all->tail=newNode;
    }
    else
    {
        all->tail->pNext=newNode;
        all->tail=newNode;
    }
    all->size++;
    return 0;
}

int allRemoveAlbum(albumll* all, char* name)
{
    if((all==NULL)||(name==NULL))
    {
        return -1;
    }
    aNode* temp1=all->head;
    aNode* temp2=NULL;
    while(temp1!=NULL)
    {
        if(strcmp(temp1->album->name,name)==0)
        {
            if(temp2==NULL)
            {
                all->head=temp1->pNext;
            }
            else
            {
                temp2->pNext=temp1->pNext;
            }
            if(temp1==all->tail)
            {
                all->tail=temp2;
            }
            aDestroy(temp1->album);
            free(temp1);
            all->size--;
            return 0;
        }
        temp2=temp1;
        temp1=temp1->pNext;
    }
    return -1;
}

void allPrint(albumll* all)
{
    if(all==NULL)
    {
        return;
    }
    aNode* temp=all->head;
    while(temp!=NULL)
    {
        aPrint(temp->album);
        temp=temp->pNext;
    }
}