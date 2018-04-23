#include <stdio.h>

#include "../global/protected_global.h"
#include <stdlib.h> 


int main(int argc, char **argv){
	const char * name = "buffdir";
	GlobalState * global;
	double lambda = 1.0;
	printf("*** REGISTERING PRODUCER TO SHARED BUFFER ON %s *** \n", name);
	getGlobalStateProtected(name, &global);
	printGlobalState(global);
	int a = rand();
	int i = 1000000;
	while(i--){
		if(i%1000)
			printf("Thread %d iter %d\n",a,1000000 - i);
		registerProducerProtected(global);
	}
	//unregisterProducerProtected(global);
	//message_creation_loop(global, lambda);
	printGlobalState(global);

	return 0;
}

