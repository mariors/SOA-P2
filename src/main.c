#include <stdio.h>

#include "global/protected_global.h"

int main(int argc, char **argv){
    const char * name = "MYSHM";
    GlobalState * global;
    getGlobalStateProtected(name,&global);

    printGlobalState(global);

    return 0;
}
