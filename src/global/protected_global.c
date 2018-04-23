#include "protected_global.h"

sem_t* getSemaphore(char* name){
	sem_t *sem = sem_open(name,  O_RDWR);
	if (sem == SEM_FAILED) {
     perror("Failed to open semphore for empty");
     exit(-1);
	}
	return sem;
}


int getGlobalStateProtected(const char *name, GlobalState **global){
	return getGlobalState(name,global);
}

void deleteGlobalStateProtected(const char *name){
	deleteGlobalState(name);
	sem_unlink("/semaphoreBuffer");
	sem_unlink("/semaphoreConsumer");
	sem_unlink("/semaphoreProducer");
}

int registerProducerProtected(GlobalState *global){
	sem_t *sem = getSemaphore("/semaphoreProducer");
	sem_wait(sem);
	int res = registerProducer(global);
	sem_post(sem);
	return res;
}

void unregisterProducerProtected(GlobalState *global){
	sem_t *sem = getSemaphore("/semaphoreProducer");
	sem_wait(sem);
	unregisterProducer(global);
	sem_post(sem);
}

int registerConsumerProtected(GlobalState *global){
	sem_t *sem = getSemaphore("/semaphoreConsumer");
	sem_wait(sem);
	int res = registerConsumer(global);
	sem_post(sem);
	return res;
}

void unregisterConsumerProtected(GlobalState *global){
	sem_t *sem = getSemaphore("/semaphoreConsumer");
	sem_wait(sem);
	unregisterConsumer(global);
	sem_post(sem);
}

ActionResponse bufferPushProtected(GlobalState *global,Message element){

	time_t start;
	time_t end;
	start = time(NULL);
	sem_t *sem = getSemaphore("/semaphoreBuffer");
	sem_wait(sem);
	end = time(NULL);
	ActionResponse ar = bufferPush(&global->buffer,element);
	sem_post(sem);
	int seconds = end - start;
	ar.time = seconds;
	return ar;
}

ActionResponse bufferPopProtected(GlobalState *global){

	time_t start;
	time_t end;
	start = time(NULL);
	sem_t *sem = getSemaphore("/semaphoreBuffer");
	sem_wait(sem);
	end = time(NULL);
	ActionResponse ar = bufferPop(&global->buffer);
	sem_post(sem);
	int seconds = end - start;
	ar.time = seconds;
	return ar;
}

int bufferIsEmptyProtected(GlobalState *global){
	return bufferIsEmpty(&global->buffer);
}

int bufferIsFullProtected(GlobalState *global){
	return bufferIsFull(&global->buffer);
}

int setSystemStatus(GlobalState* global,status_code s){
	global->status = s;
}

int checkSystemAlive(GlobalState* global){
	return global->status == RUNNING;
}
