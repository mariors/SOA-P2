//
// Created by aleph on 4/19/18.
//
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "exponential.h"
#define MAX_RANGE 100000


double sample_exponential(double lambda) {
    double u = (rand()%MAX_RANGE)/(double)MAX_RANGE;
    return -1/lambda * log(1-u); //inverse of exponential distribution pdf.
}


int wait_on_exponential_dist(double lambda) {
    double s = sample_exponential(lambda);
    int abs_s = (int) s;
    int abs_nsec = (int)(s - abs_s)*10E9;
    printf("Waiting for %d s %d ms\n",abs_s,abs_nsec/1000000);

    nanosleep(&(struct timespec){.tv_sec=abs_s,.tv_nsec=abs_nsec},NULL);
	
    return abs_s;
}

double wait_arbitrary_secs(int s){
    nanosleep(&(struct timespec){.tv_sec=s,.tv_nsec=0},NULL);
    return s;
}
