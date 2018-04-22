#ifndef GLOBAL_H
#define GLOBAL_H

#include "share/share_base.h"

void mapGlobalState(int fd, GlobalState **global);

int getGlobalState(const char *name, GlobalState **global);

void deleteGlobalState(const char *name);

void printGlobalState(GlobalState *global);

#endif