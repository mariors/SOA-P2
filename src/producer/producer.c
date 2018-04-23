#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../global/protected_global.h"
#include "../global/time/exponential.h"

//Returns random element between 0 and 4
int random_element() {
	return rand() % 5;
}

int main(int argc, char **argv){
	if(argc != 3){
		printf("ERROR: Provide the following arguments(name,exponentialDistribution)\n");
		return -1;
	}

	const char * name = argv[1];
	double lambda = atof(argv[2]);

	printf("PRODUCER: Iniciando\n");
	printf("PRODUCER: Share Memory: %s\n",name);
	printf("PRODUCER: Exponential distribution: %f\n",lambda);

	GlobalState * global;
	printf("PRODUCER: Getting GlobalState %s\n", name);
	int g = getGlobalStateProtected(name, &global);
	if(g==ERROR_IMPOSIBLE_CREATE_OPEN_SHARE_MEMORY){
		printf("ERROR: Imposible to Create or Open the Share Memory\n");
	}else{
		printf("PRODUCER:GlobalState Open\n");
		printGlobalState(global);
		int uid = registerProducerProtected(global);
		printf("PRODUCER: Register Producer with id: %d\n", uid);

		printf("PRODUCER: Entering to loop\n");
		while(1){
			wait_on_exponential_dist(lambda);
			Message m = createNewMessage(uid,random_element());
			printf("PRODUCER: Pushing message to queue: %d\n", m.id);
			printMessage(m);
			int p = bufferPushProtected(global,m);
			if(p==-1){
				printf("ERROR: Buffer is FULL imposible to insert new element\n");
			}
			printGlobalState(global);
		}
	}
	return 0;
}

