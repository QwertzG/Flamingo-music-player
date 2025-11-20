#include "playlistcll.h"

pcll* pcllCreate()
{
    pcll* pill = (pcll*)malloc(sizeof(pcll));
    pill->current=NULL;
    pill->size=0;
    return pill;
}

void pcllClear(pcll* pcll)
{
    if(pcll==NULL)
    {
        return;
    }
    pNode* temp1=pcll->current;
    pNode* temp2=NULL;
    int n2f=pcll->size;
    while(n2f>0)
    {
        temp2=temp1->pNext;
        free(temp1);
        temp1=temp2;
        n2f--;
    }
    pcll->current=NULL;
    pcll->size=0;
}

void pcllDestroy(pcll* pcll)
{
    pcllClear(pcll);
    free(pcll);
}

int pcllAddSong(pcll* pcll, song* gaana)
{
    if((pcll==NULL)||(gaana==NULL))
    {
        return -1;
    }
    pNode* newNode=(pNode*)malloc(sizeof(pNode));
    newNode->song=gaana;
    if(pcll->current==NULL)
    {
        newNode->pNext=newNode;
        pcll->current=newNode;
    }
    else
    {
        pNode* temp=pcll->current;
        while(temp->pNext!=pcll->current)
        {
            temp=temp->pNext;
        }
        newNode->pNext=pcll->current;
        temp->pNext=newNode;
    }
    pcll->size++;
    return 0;
}

song* pcllRemoveCurrentSong(pcll* pcll)
{
    if(pcll==NULL)
    {
        return NULL;
    }
    pNode* temp=pcll->current;
    song* gaana=temp->song;
    if(pcll->size==1)
    {
        pcll->current=NULL;
    }
    else
    {
        pNode* temp2=pcll->current;
        while(temp2->pNext!=pcll->current)
        {
            temp2=temp2->pNext;
        }
        temp2->pNext=pcll->current->pNext;
        pcll->current=pcll->current->pNext;
    }
    free(temp);
    pcll->size--;
    return gaana;
}

void pcllPrint(pcll* pcll)
{
    if((pcll==NULL)||(pcll->current==NULL))
    {
        return;
    }
    pNode* temp=pcll->current;
    int count=0, sno=1;
    while(count<pcll->size)
    {
        if(count==0)
        {
            printf("=> ");
        }
        else
        {
            printf("   ");
        }
        printf("%d. ",sno);
        sPrint(temp->song);
        temp=temp->pNext;
        sno++;
        count++;
    }
}

song* pcllNextSong(pcll* pcll)
{
    if((pcll==NULL)||(pcll->current==NULL))
    {
        return NULL;
    }
    pcll->current=pcll->current->pNext;
    return pcll->current->song;
}

song* pcllPreviousSong(pcll* pcll)
{
    if((pcll==NULL)||(pcll->current==NULL))
    {
        return NULL;
    }
    pNode* temp = pcll->current;
    while(temp->pNext!=pcll->current)
    {
        temp = temp->pNext;
    }
    pcll->current=temp;
    return pcll->current->song;
}