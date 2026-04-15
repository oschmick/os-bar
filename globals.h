/*
 * globals.h
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

// number of customer threads
extern int num_threads;

// TODO - declare some semaphores
extern sem_t *customer_enters;
extern sem_t *order;
extern sem_t *drink_made;
extern sem_t *pay_bartender;
extern sem_t *customer_leaves;

#endif /* GLOBALS_H_ */
