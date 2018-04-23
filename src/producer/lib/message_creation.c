//
// Created by aleph on 4/21/18.
//

#include "../../global/protected_global.h"
#include "../../global/time/exponential.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "message_creation.h"

void message_creation_loop(GlobalState* global,double lambda){
	printf("Producer: Entering loop\n");
	while(1) {
		wait_on_exponential_dist(lambda);
		Message m = {random_element()};
		printf("Producer: Pushing message to queue: %d\n", m.id);
		bufferPushProtected(global,m);
		printGlobalState(global);
	}
}


//Returns random element between 0 and 4
int random_element() {
	return rand() % 5;
}