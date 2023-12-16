#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

/* Global Variables */
int readcnt;    /* Initially = 0 */
pthread_mutex_t counter_lock, write_lock;

void lock_for_writing(void) {
    pthread_mutex_lock(&write_lock);
}

void unlock_for_writing(void) {
    pthread_mutex_unlock(&write_lock);
}

void lock_for_reading(void) {
    pthread_mutex_lock(&counter_lock);
    readcnt++;
    if (readcnt == 1) {  /* I am the first reader that comes in critical section. Now writer stop */
        pthread_mutex_lock(&write_lock);
    }
    pthread_mutex_unlock(&counter_lock);
}

void unlock_for_reading(void) {
    pthread_mutex_lock(&counter_lock);
    readcnt--;
    if (readcnt == 0) {     /* I am the last reader that comes out critical section. Now writer can come. */
        pthread_mutex_unlock(&write_lock);
    }
    pthread_mutex_unlock(&counter_lock);
}