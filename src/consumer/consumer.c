#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../global/protected_global.h"
#include "../global/time/exponential.h"

void printAction(int pid, int internal_id, int idx, int producers, int consumers){

	printf("\nConsumer PID: %d\nConsumer internal ID: %d\nMessage read from index: %d\nProducers alive: %d\nConsumers alive: %d\n", pid, internal_id, idx, producers, consumers);

}

void printShutdown(int pid, int internal_id, int msgs, double acc_waiting_time, double acc_blocked_time){

	printf("\nConsumer PID: %d\nConsumer internal ID: %d\nTotal messages read: %d\nAccumulated time waiting: %d\nAccumulated time blocked: %d\n\nSHUTING DOWN...\n", pid, internal_id, msgs, acc_waiting_time, acc_blocked_time);

}


int main(int argc, char **argv){

	if(argc != 3){
		printf("ERROR: Provide the following arguments(name,exponentialDistribution)\n");
		return -1;
	}

	const char * name = argv[1];
	double lambda = atof(argv[2]);

	printf("CONSUMER: Iniciando\n");
	printf("CONSUMER: Share Memory: %s\n",name);
	printf("CONSUMER: Exponential distribution: %f\n",lambda);

	int pid = getpid();
	int mod_5 = pid % 5;


	double acc_waiting_time = 0;
	double acc_blocked_time = 0;
	int msgs = 0;

	
	GlobalState * global;
	printf("CONSUMER: Getting GlobalState %s\n", name);
 	int g = getGlobalStateProtected(name, &global);
 	if(g==ERROR_IMPOSIBLE_CREATE_OPEN_SHARE_MEMORY){
 		printf("ERROR: Imposible to Create or Open the Share Memory\n");
		return -1;
 	}	


	printf("CONSUMER:GlobalState Open\n");
	printGlobalState(global);

	printf("*** REGISTERING CONSUMER TO SHARED BUFFER ON %s *** \n", name);

	int internal_id = registerConsumerProtected(global);
	printf("CONSUMER: Registered Consumer with id: %d\n", internal_id);

	printf("CONSUMER: Entering to loop\n");


	int read_idx = 0;

	while(1){
		acc_waiting_time += wait_on_exponential_dist(lambda);
		printf("CONSUMER: Reading message from queue...\n");
		Message m = bufferPopProtected(global);
		printAction(pid, internal_id, read_idx, global->producer.total, global->consumer.total);
		msgs++;
		if(m.key == -1 || m.key == mod_5){
			break;		
		}
	}

	printf("*** UNREGISTERING CONSUMER TO SHARED BUFFER ON %s *** \n", name);
	
	unregisterConsumerProtected(global);

	printShutdown(pid, internal_id, msgs, acc_waiting_time, acc_blocked_time);

	return 0;


}
