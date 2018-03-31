#ifndef SHARE_BASE_H
#define SHARE_BASE_H

#include "buffer/buffer_base.h"
#include <sys/mman.h>
#include <fcntl.h>

typedef struct Integer{
    int total;
    int unique;
} Integer;

struct GlobalStateStruct{
    Integer producer;
    Integer consumer;
    Buffer buffer;
} GlobalStateDefault;

typedef struct GlobalStateStruct GlobalState;

#define ERROR_CREATE_SHARE_MEMORY -1
#define ERROR_OPEN_SHARE_MEMORY -2
#define ERROR_IMPOSIBLE_CREATE_OPEN_SHARE_MEMORY -3

void fixMemoryToGlobalState(int fd){
    ftruncate(fd, sizeof(GlobalState));
}

int createShareMemory(const char *name){
    int fd = shm_open(name, O_RDWR|O_CREAT|O_EXCL, 0);
    if(fd == -1) {
        return ERROR_CREATE_SHARE_MEMORY;
    }
    fixMemoryToGlobalState(fd);
    return fd;
}

int openShareMemory(const char *name){
    int fd = shm_open(name, O_RDWR|O_CREAT, 0);
    if(fd == -1) {
        return ERROR_OPEN_SHARE_MEMORY;
    }
    fixMemoryToGlobalState(fd);
    return fd;
}

void deleteShareMemory(const char *name){
    shm_unlink(name);
}

int registerProducer(GlobalState *global){
    global->producer.total++;
    global->producer.unique++;
    return global->producer.unique;
}

void unregisterProducer(GlobalState *global){
    if(global->producer.total>0){
        global->producer.total--;
    }
}

int registerConsumer(GlobalState *global){
    global->consumer.total++;
    global->consumer.unique++;
    return global->consumer.unique;
}

void unregisterConsumer(GlobalState *global){
    if(global->consumer.value>0){
        global->consumer.value--;
    }
}



#endif