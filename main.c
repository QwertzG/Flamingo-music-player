#include <stdio.h>
#include "src/cli/cli.h"
#include "src/storage/cmdlog.h"

int main()
{
    cli* cl=cliCreate();
    if(cl==NULL)
    {
        printf("[ERROR] Failed to initialise application\n");
        return 1;
    }
    if(cliInitialise(cl)!=0)
    {
        printf("[ERROR] Failed to load application data\n");
        cliDestroy(cl);
        return 1;
    }
    cliDisplayWelcome();
    cliRun(cl);
    logClose();
    cliDestroy(cl);
    return 0;
}
