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

void fixMemoryToGlobalState(int fd);

int createShareMemory(const char *name);

int openShareMemory(const char *name);

void deleteShareMemory(const char *name);

int registerProducer(GlobalState *global);

void unregisterProducer(GlobalState *global);

int registerConsumer(GlobalState *global);

void unregisterConsumer(GlobalState *global);

#endif