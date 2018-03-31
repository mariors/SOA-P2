#ifndef PROTECTED_GLOBAL_H
#define PROTECTED_GLOBAL_H

#include "global/global.h"

/*
    const char * name = "MYSHM";

    GlobalState *global;
    //deleteGlobalStateProtected(name);
    int r = getGlobalStateProtected(name,&global);
    registerProducerProtected(global);
    Message msg1;msg1.id = 1;
    //bufferPushProtected(global,msg1);
    bufferPopProtected(global);
    printGlobalState(global);
*/

int getGlobalStateProtected(const char *name, GlobalState **global){
    return getGlobalState(name,global);
}

void deleteGlobalStateProtected(const char *name){
    deleteGlobalState(name);
}

void registerProducerProtected(GlobalState *global){
    global->producer.value++;
}

void unregisterProducerProtected(GlobalState *global){
    if(global->producer.value>0){
        global->producer.value--;
    }
}

void registerConsumerProtected(GlobalState *global){
    global->consumer.value++;
}

void unregisterConsumerProtected(GlobalState *global){
    if(global->producer.value>0){
        global->consumer.value--;
    }
}

int bufferPushProtected(GlobalState *global,Message element){
    bufferPush(&global->buffer,element);
}

int bufferPopProtected(GlobalState *global){
    bufferPop(&global->buffer);
}

#endif