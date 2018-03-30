#ifndef SHARE_BASE_H
#define SHARE_BASE_H

#include<stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

struct GlobalStateStruct{
    int producer;
    int consumer;
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



#endif