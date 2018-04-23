#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../global/protected_global.h"
#include "../global/time/exponential.h"

//Returns random element between 0 and 4
int random_element() {
	return rand() % 5;
}

void printAction(int pid, int internal_id, int idx, int producers, int consumers){

	printf("\nProducer PID: %d\nProducer internal ID: %d\nMessage read from index: %d\nProducers alive: %d\nConsumers alive: %d\n", pid, internal_id, idx, producers, consumers);

}

void printShutdown(int pid, int internal_id, int msgs, int acc_waiting_time, int acc_blocked_time){

	printf("\nProducer PID: %d\nProducer internal ID: %d\nTotal messages read: %d\nAccumulated time waiting: %d\nAccumulated time blocked: %d\n\nSHUTING DOWN...\n", pid, internal_id, msgs, acc_waiting_time, acc_blocked_time);

}

int main(int argc, char **argv){
	if(argc != 3){
		printf("ERROR: Provide the following arguments(name,exponentialDistribution)\n");
		return -1;
	}

	const char * name = argv[1];
	double lambda = atof(argv[2]);

	int pid = getpid();

	int acc_waiting_time = 0;
	int acc_blocked_time = 0;
	int msgs = 0;

	printf("PRODUCER: Iniciando\n");
	printf("PRODUCER: Share Memory: %s\n",name);
	printf("PRODUCER: Exponential distribution: %f\n",lambda);

	GlobalState * global;
	printf("PRODUCER: Getting GlobalState %s\n", name);
	int g = getGlobalStateProtected(name, &global);
	if(g==ERROR_IMPOSIBLE_CREATE_OPEN_SHARE_MEMORY){
		printf("ERROR: Imposible to Create or Open the Share Memory\n");
		return -1;
	}else{
		printf("PRODUCER:GlobalState Open\n");
		printGlobalState(global);

		printf("*** REGISTERING PRODUCER TO SHARED BUFFER ON %s *** \n", name);

		int uid = registerProducerProtected(global);
		printf("PRODUCER: Register Producer with id: %d\n", uid);

		printf("PRODUCER: Entering to loop\n");

		while(1){
			if(!checkSystemAlive(global)){
				break;
			}
			acc_waiting_time += wait_on_exponential_dist(lambda);
			Message m = createNewMessage(uid,random_element());
			printf("PRODUCER: Pushing message to queue...\n");
			printMessage(m);
			ActionResponse ar = bufferPushProtected(global,m);
			acc_blocked_time =+ ar.time;
			if(ar.idx==-1){
				printf("ERROR: Buffer is FULL imposible to insert new element\n");
			}else{
				msgs++;
				printAction(pid, uid, ar.idx, global->producer.total, global->consumer.total);
			}
		}

		printf("*** UNREGISTERING PRODUCER TO SHARED BUFFER ON %s *** \n", name);

		unregisterProducerProtected(global);

		printShutdown(pid, uid, msgs, acc_waiting_time, acc_blocked_time);

	}
	printGlobalState(global);
	return 0;
}

