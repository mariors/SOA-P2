#include "buffer/buffer_base.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "share_base.h"

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
	if(global->consumer.total>0){
		global->consumer.total--;
	}
}