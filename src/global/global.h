#ifndef GLOBAL_H
#define GLOBAL_H

#include "share/share_base.h"


int getGlobalState(const char *name, GlobalState **global){
    int fd = createShareMemory(name);
    printf("try to create share memory\n");
    if(fd==ERROR_CREATE_SHARE_MEMORY) {
        printf("error to create share memory\n");
        printf("try to open share memory\n");
        fd = openShareMemory(name);
        if(fd==ERROR_OPEN_SHARE_MEMORY){
            return ERROR_IMPOSIBLE_CREATE_OPEN_SHARE_MEMORY;
        }
    }
    printf("Socket: %d\n",fd);
    *global = mmap(NULL, sizeof(GlobalState), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    return 1;
}

void deleteGlobalState(const char *name){
    printf("Deleting Global State\n");
    deleteShareMemory(name);
}

void printGlobalState(GlobalState *global){
    printf("Global State\n");
    printf("Producers: %d\n",global->producer);
    printf("Consumers: %d\n",global->consumer);
}

#endif