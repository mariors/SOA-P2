#ifndef PROTECTED_GLOBAL_H
#define PROTECTED_GLOBAL_H

#include "global/global.h"

int getGlobalStateProtected(const char *name, GlobalState **global){
    return getGlobalState(name,global);
}

void deleteGlobalStateProtected(const char *name){
    deleteGlobalState(name);
}

int registerProducerProtected(GlobalState *global){
    return registerProducer(global);
}

void unregisterProducerProtected(GlobalState *global){
    unregisterProducer(global);
}

int registerConsumerProtected(GlobalState *global){
    return registerConsumer(global);
}

void unregisterConsumerProtected(GlobalState *global){
    unregisterConsumer(global);
}

int bufferPushProtected(GlobalState *global,Message element){
    bufferPush(&global->buffer,element);
}

int bufferPopProtected(GlobalState *global){
    bufferPop(&global->buffer);
}

#endif


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