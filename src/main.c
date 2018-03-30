#include <stdio.h>

#include "global/global.h"

int main(int argc, char **argv){
    const char * name = "MYSHM";

    GlobalState *global;
    deleteGlobalState(name);
    int r = getGlobalState(name,&global);
    printf("Return %d\n",r);
    //global->producer = 0;
    //global->consumer = 0;
    global->producer++;
    printGlobalState(global);

    return 0;
}
