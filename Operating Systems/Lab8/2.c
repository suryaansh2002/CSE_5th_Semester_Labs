#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
int buf[5], f, r;
sem_t mutex_sem, end, start;
void *writer(void *arg)
{
    while (1)
    {
        sem_wait(&mutex_sem);
        printf("Incrementing no. %d in writer\n", f);
        f++;
        sleep(1);
        sem_post(&mutex_sem);
        sleep(1);
    }
}
void *reader(void *arg)
{
    while (1)

    {
        sem_wait(&mutex_sem);
        printf("Read Item is : %d\n", f);
        sleep(1);
        sem_post(&mutex_sem);
        sleep(1);
    }
}
int main()
{
    pthread_t t1, t2;
    sem_init(&mutex_sem, 0, 1);
    sem_init(&end, 0, 1);
    sem_init(&start, 0, 10);
    pthread_create(&t1, NULL, &reader, NULL);
    pthread_create(&t2, NULL, &writer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}