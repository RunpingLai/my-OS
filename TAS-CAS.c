#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/* Atomic Operations */

typedef struct lock_t 
{
    int flag;   
} lock_t;
volatile lock_t mylock;
int TestAndSet(lock_t *lock)
{
    int old_val = lock->flag;
    lock->flag = 1;
    return old_val;
}

// volatile int lock = 0;
void lock(lock_t *lock)
{
    /* Someone is still acquiring this lock */
    while(TestAndSet(lock) == 1) {
        printf("testing and setting\n");
    }
}

void unlock(lock_t *lock)
{
    lock->flag = 0;
}

void* t1_actions(void* tid) {
    printf("t1 started\n");
    lock(&mylock);
    printf("t1 acquired the lock\n");
    sleep(5);
    printf("5 seconds has passed. t2 should get the lock now\n");
    unlock(&mylock);
}

void* t2_actions(void* tid) {
    printf("t2 started. Trying to get the lock\n");
    lock(&mylock);
    printf("t2 got the lock\n");
    unlock(&mylock);
}

int main()
{
    pthread_t t1, t2;
    
    int status1 = pthread_create(&t1, NULL, t1_actions, NULL);
    
    sleep(1);
    int status2 = pthread_create(&t2, NULL, t2_actions, NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return 1;
}
