//
// Created by aleph on 4/21/18.
//


#include "../global.h"
#include "../time/exponential.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "message_consumption.h"

void message_consumption_on_loop(GlobalState* global,double lambda){
	printf("Consumer: Entering loop\n");
	while(1) {
		wait_on_exponential_dist(lambda);
		Message m = bufferPop(&global->buffer);
		printf("Consumer: read message: %d\n", m.id);
		//TODO: check condition, if consumperPid%5 == m.id, DIE.
		printGlobalState(global);
	}
}