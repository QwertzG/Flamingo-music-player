#ifndef CMDLOG_H
#define CMDLOG_H
#include <time.h>
#include <string.h>

typedef enum
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_COMMAND
}LogLevel;

int logInitialise(char* filepath);
void logClose();
int logCommand(char* cmd);
int logMessage(LogLevel level, char* message);
void logDisplayHistory();
int logCommandCount();

#endif