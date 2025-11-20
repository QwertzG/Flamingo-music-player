#include "cmdlog.h"
#include "fileio.h"

static FILE* logf=NULL;
static char logpath[512]={0};
static int logcount=0;

static char* timestamp()
{
    static char timestamp[64];
    time_t now=time(NULL);
    struct tm* tm_info=localtime(&now);
    strftime(timestamp,sizeof(timestamp),"%d-%m-%Y %H:%M:%S",tm_info);
    return timestamp;
}

int logInitialise(char* filepath)
{
    if(filepath==NULL)
    {
        return -1;
    }
    strncpy(logpath,filepath,sizeof(logpath)-1);
    logpath[sizeof(logpath)-1]='\0';
    logf=fopen(filepath,"a");
    if(logf==NULL)
    {
        printf("[ERROR] Could not open log file: %s\n",filepath);
        return -1;
    }
    fprintf(logf, "\n=============== %s ===============\n", timestamp());
    fflush(logf);
    printf("[INFO] Command Logger initialised. Log file: %s\n",filepath);
    return 0;
}

void logClose()
{
    if(logf!=NULL)
    {
        fprintf(logf,"=============== %s ===============\n\n",timestamp());
        fflush(logf);
        fclose(logf);
        logf=NULL;
    }
}

int logCommand(char* cmd)
{
    if(cmd==NULL)
    {
        return -1;
    }
    if(logf==NULL)
    {
        if(logInitialise(logpath)!=0)
        {
            return -1;
        }
    }
    fprintf(logf,"[%s] COMMAND: %s\n",timestamp(),cmd);
    fflush(logf);
    logcount++;
    return 0;
}

int logMessage(LogLevel level, char* message)
{
   if(message==NULL)
   {
        return -1;
   }
   if(logf==NULL)
   {
        return -1;
   }
   char* strlevel;
   if(level==LOG_INFO)
   {
        strlevel="[INFO]";    
   }
   else if(level==LOG_WARNING)
   {
        strlevel="[WARNING]";
   }
   else if(level==LOG_ERROR)
   {
        strlevel="[ERROR]";
   }
   else if(level==LOG_COMMAND)
   {
        strlevel="[COMMAND]";
   }
   else
   {
        strlevel="[UNKNOWN]";
   }

   fprintf(logf,"[%s] %s %s\n",timestamp(),strlevel,message);
   fflush(logf);
   return 0;
}

void logDisplayHistory()
{
    if(fioExists("data/commandHistory.txt")==0)
    {
        printf("No command history found.\n");
        return;
    }
    FILE* file=fopen("data/commandHistory.txt","r");
    if(file==NULL)
    {
        printf("[ERROR] Could not open log file\n");
        return;
    }
    printf("\n========== COMMAND HISTORY ==========\n\n");
    char buff[1024];
    int c=0;
    while(fioReadLine(file,buff,sizeof(buff))!=NULL)
    {
        if(strstr(buff,"[COMMAND]")!=NULL)
        {
            printf("%s\n",buff);
            c++;
        }
    }
    printf("\n========== Total Commands: %d ==========\n\n", c);
    fclose(file);
}

int logCommandCount()
{
    return logcount;
}