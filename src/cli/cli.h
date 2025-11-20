#ifndef CLI_H
#define CLI_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../library/musiclibrary.h"
#include "../player/player.h"
#include "../storage/cmdlog.h"

typedef struct cli
{
    library* library;
    player* player;
    int running;
}cli;

cli* cliCreate();
void cliDestroy(cli* cli);
int cliInitialise(cli* cli);
void cliRun(cli* cli);
void cliDisplayWelcome();
void cliDisplayHelp();
void cliDisplayPrompt();
void cliHandleCommand(cli* cli,char* command);


#endif