#ifndef PROTECTED_GLOBAL_H
#define PROTECTED_GLOBAL_H

#include "global/global.h"

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