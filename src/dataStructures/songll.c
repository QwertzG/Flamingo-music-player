#include "songll.h"

songll* sllCreate()
{
    songll* newLL = (songll*)malloc(sizeof(songll));
    newLL->head=newLL->tail=NULL;
    newLL->size=0;
    return newLL;
}

void sllDestroy(songll* sll)
{
    if(sll==NULL)
    {
        return;
    }
    sNode* temp=sll->head;
    while (temp!=NULL)
    {
        sNode* temp2=temp->pNext;
        free(temp);
        temp=temp2;
    }
    sll->head=NULL;
    sll->size=0;
    sll->tail=NULL;
    free(sll);
}

int sllAddSong(songll* sll, song* gaana)
{
    if((sll==NULL)||(gaana==NULL))
    {
        return -1;
    }
    sNode* newNode = (sNode*)malloc(sizeof(sNode));
    newNode->song=gaana;
    newNode->pNext=NULL;
    if(sll->tail==NULL)
    {
        sll->head=newNode;
        sll->tail=newNode;
    }
    else
    {
        sll->tail->pNext=newNode;
        sll->tail=newNode;
    }
    sll->size++;
    return 0;
}

int sllRemoveSong(songll* sll, char* title)
{
    if((sll==NULL)||(title==NULL))
    {
        return -1;
    }
    sNode* temp1=sll->head;
    sNode* temp2=NULL;
    while(temp1!=NULL)
    {
        if(strcmp(temp1->song->title,title)==0)
        {
            if(temp2==NULL)
            {
                sll->head=temp1->pNext;
            }
            else
            {
                temp2->pNext=temp1->pNext;
            }
            if(temp1==sll->tail)
            {
                sll->tail=temp2;
            }
            free(temp1);
            sll->size--;
            return 0;
        }
        temp2=temp1;
        temp1=temp1->pNext;
    }
    return -1;
}

void sllPrint(songll* sll)
{
    if(sll==NULL)
    {
        return;
    }
    sNode* temp = sll->head;
    while (temp!=NULL)
    {
        sPrint(temp->song);
        temp=temp->pNext;
    } 
}

song* sllFind(songll* sll, char* title)
{
    if((sll==NULL)||(title==NULL))
    {
        return NULL;
    }
    sNode* temp=sll->head;
    while(temp!=NULL)
    {
        if(strcmp(temp->song->title,title)==0)
        {
            return temp->song;
        }
        temp=temp->pNext;
    }
    return NULL;
}