//#ifndef PROTECTED_GLOBAL_H
//#define PROTECTED_GLOBAL_H

#include "global/global.h"

int getGlobalStateProtected(const char *name, GlobalState **global);

void deleteGlobalStateProtected(const char *name);
int registerProducerProtected(GlobalState *global);

void unregisterProducerProtected(GlobalState *global);

int registerConsumerProtected(GlobalState *global);

void unregisterConsumerProtected(GlobalState *global);

int bufferPushProtected(GlobalState *global,Message element);

int bufferIsEmptyProtected(GlobalState *global);

int bufferIsFullProtected(GlobalState *global);

Message bufferPopProtected(GlobalState *global);

//
//#endif


/*
    const char * name = "MYSHM";

    GlobalState *global;
    deleteGlobalStateProtected(name);
    int r = getGlobalStateProtected(name,&global);
    registerProducerProtected(global);
    registerProducerProtected(global);
    registerProducerProtected(global);
    registerProducerProtected(global);
    unregisterProducerProtected(global);
    registerConsumerProtected(global);
    registerConsumerProtected(global);
    registerConsumerProtected(global);
    unregisterConsumerProtected(global);
    Message msg1;msg1.id = 1;
    bufferPushProtected(global,msg1);
    bufferPushProtected(global,msg1);
    bufferPushProtected(global,msg1);
    bufferPushProtected(global,msg1);
    bufferPopProtected(global);
    printGlobalState(global);
*/