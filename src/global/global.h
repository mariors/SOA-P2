#ifndef GLOBAL_H
#define GLOBAL_H

#include "share/share_base.h"


void mapGlobalState(int fd, GlobalState **global){
    *global = mmap(NULL, sizeof(GlobalState), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
}

int getGlobalState(const char *name, GlobalState **global){
    int create = 0;
    int fd = createShareMemory(name);
    //printf("try to create share memory\n");
    if(fd==ERROR_CREATE_SHARE_MEMORY) {
        //printf("error to create share memory\n");
        //printf("try to open share memory\n");
        fd = openShareMemory(name);
        if(fd==ERROR_OPEN_SHARE_MEMORY){
            return ERROR_IMPOSIBLE_CREATE_OPEN_SHARE_MEMORY;
        }
    }else{
        create=1;
    }
    printf("Socket: %d\n",fd);

    mapGlobalState(fd,global);

    //force to initialize if it is created for first time
    if(create){
        (*global)->buffer = BufferDefault;
    }
    
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
    bufferPrintDetails(&global->buffer);
}

#endif