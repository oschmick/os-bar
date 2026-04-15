/*
 * thebar.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();

int num_threads;
sem_t *customer_enters;
sem_t *order;
sem_t *drink_made;
sem_t *pay_bartender;
sem_t *customer_leaves;

/**
 * Main function
 */
int main(int argc, char *argv[]) {
	// TODO - read the command-line argument into the `num_threads` global (already declared)
	if (argc != 2) {
		printf("Usage: ./thebarSol <num customers>\n");
		exit(1);
	}
	num_threads = atoi(argv[1]);

	if (num_threads < 1) {
		printf("num_threads must be >= 1\n");
	}

	printBanner();
	init(); // initialize semaphores

	// TODO - spawn customer threads
	// TODO - spawn bartender thread
	pthread_t *cust = malloc(num_threads * sizeof(pthread_t));
	pthread_t *bart = malloc(sizeof(pthread_t));
	unsigned int *ids = malloc(num_threads * sizeof(unsigned int));

	for (int i=0; i<num_threads; i++) {
		ids[i] = i;
		pthread_create(&cust[i], NULL, customer, &ids[i]);
	}
	pthread_create(bart, NULL, bartender, NULL);

	for (int i=0; i<num_threads; i++) {
		pthread_join(cust[i], NULL);
	}
	pthread_join(*bart, NULL);

	cleanup(); // cleanup and destroy semaphores
	free(cust);
	free(bart);
	free(ids);
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner() {
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init() {
	sem_unlink("/customer_enters");
	sem_unlink("/order");
	sem_unlink("/drink_made");
	sem_unlink("/pay_bartender");
	sem_unlink("/customer_leaves");
	
	// TODO - create semaphores here
	customer_enters = sem_open("/customer_enters", O_CREAT, 0600, 0);
	order = sem_open("/order", O_CREAT, 0600, 0);
	drink_made = sem_open("/drink_made", O_CREAT, 0600, 0);
	pay_bartender = sem_open("/pay_bartender", O_CREAT, 0600, 0);
	customer_leaves = sem_open("/customer_leaves", O_CREAT, 0600, 1);
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup() {
	// TODO - close and destroy semaphores
	sem_close(customer_enters);
	sem_close(order);
	sem_close(drink_made);
	sem_close(pay_bartender);
	sem_close(customer_leaves);

	sem_unlink("/customer_enters");
	sem_unlink("/order");
	sem_unlink("/drink_made");
	sem_unlink("/pay_bartender");
	sem_unlink("/customer_leaves");
}
