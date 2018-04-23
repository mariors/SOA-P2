#include "protected_global.h"


int getGlobalStateProtected(const char *name, GlobalState **global){
	return getGlobalState(name,global);
}

void deleteGlobalStateProtected(const char *name){
	deleteGlobalState(name);
}

int registerProducerProtected(GlobalState *global){
	sem_t *sem = sem_open("/semaphore1112",  O_RDWR);
	if (sem == SEM_FAILED) {
     perror("Failed to open semphore for empty");
     exit(-1);
	}
	sem_wait(sem);
	int res = registerProducer(global);
	sem_post(sem);
	printf("Done\n");
	//em_close(sem);
	//sem_unlink("/semaphore");
	return res;
}

void unregisterProducerProtected(GlobalState *global){
	sem_wait(&global->mutex_producer);
	unregisterProducer(global);
	sem_post(&global->mutex_producer);
}

int registerConsumerProtected(GlobalState *global){
	sem_wait(&global->mutex_consumer);
	int res = registerConsumer(global);
	sem_post(&global->mutex_consumer);
	return res;
}

void unregisterConsumerProtected(GlobalState *global){
	sem_wait(&global->mutex_consumer);
	unregisterConsumer(global);
	sem_post(&global->mutex_consumer);

}

ActionResponse bufferPushProtected(GlobalState *global,Message element){

	printf("before mutex\n");
	time_t start;
	time_t end;
	start = time(NULL);
	sem_wait(&global->buffer.mutex);
	end = time(NULL);
	printf("inside mutex");
	ActionResponse ar = bufferPush(&global->buffer,element);
	sem_post(&global->buffer.mutex);
	printf("after mutex");
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

ActionResponse bufferPopProtected(GlobalState *global){

	time_t start;
	time_t end;
	start = time(NULL);
	sem_wait(&global->buffer.mutex);
	end = time(NULL);
	ActionResponse ar = bufferPop(&global->buffer);
	sem_post(&global->buffer.mutex);
	int seconds = end - start;
	ar.time = seconds;
	return ar;
}

int setSystemStatus(GlobalState* global,status_code s){
	//todo; semaphore
	global->status = s;
}

int checkSystemAlive(GlobalState* global){
	//todo; semaphore
	return global->status == RUNNING;
}
