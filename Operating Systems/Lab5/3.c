#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *thread_code(void *args)
{
    int *arr = (int *)args;
    int l = arr[0];
    int u = arr[1];
    int *sieve = (int *)calloc(u + 1, sizeof(int));
    for (int i = 0; i <= u; i++)
    {
        sieve[i] = 1;
    }
    sieve[0] = 0;
    sieve[1] = 0;
    for (int i = 2; i * i <= u; i++)
    {
        if (sieve[i] == 1)
        {
            for (int j = i * i; j <= u; j += i)
            {
                sieve[j] = 0;
            }
        }
    }
    return (void *)sieve;
}
int main()
{

    int arr[2];
    printf("Enter lower: ");
    scanf("%d", &arr[0]);
    printf("Enter higher: ");
    scanf("%d", &arr[1]);
    int *result;
    pthread_t thread;
    pthread_create(&thread, 0, &thread_code, (void *)arr);
    pthread_join(thread, (void **)&result);
    printf("The Prime Numbers are: ");
    for (int i = arr[0]; i < arr[1]; i++)
    {
        if ((result)[i])
            printf("%d ", i);
    }
    printf("\n");
    return 0;
}