#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Mem
{
    int offset;
    int size;
    int allocated;
};
typedef struct Mem mem;
mem arr[10];
int sizes[] = {5, 6, 4, 7, 3, 8, 2, 9, 1, 5};

void printmem()
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d: offset: %d, size: %d, allocated: %d\n", i, arr[i].offset, arr[i].size, arr[i].allocated);
    }
}

void memCheck(int size)
{
    int choice = 0;
    printf("1. first fit\t2. best fit\t3. worst fit\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (arr[i].size - arr[i].allocated >= size)
            {
                printf("memory available at position %d\n", i);
                break;
            }
        }
    }
    else if (choice == 2)
    {
        int bestPos = -1;
        int bestRem = INT_MAX;
        for (int i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem < bestRem)
                {
                    bestRem = rem;
                    bestPos = i;
                }
            }
        }
        printf("memory available at position %d\n", bestPos);
    }
    else if (choice == 3)
    {
        int worstPos = -1;
        int worstRem = INT_MIN;
        for (int i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem > worstRem)
                {
                    worstRem = rem;
                    worstPos = i;
                }
            }
        }
        printf("memory available at position %d\n", worstPos);
    }
    else
    {
        printf("invalid choice\n");
    }
}

void memAlloc(int size)
{
    int choice = 0;
    printf("1. first fit\t2. best fit\t3. worst fit\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (arr[i].size - arr[i].allocated >= size)
            {
                arr[i].allocated += size;
                printf("memory allocated at position %d\n", i);
                break;
            }
        }
    }
    else if (choice == 2)
    {
        int bestPos = -1;
        int bestRem = INT_MAX;
        for (int i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem < bestRem)
                {
                    bestRem = rem;
                    bestPos = i;
                }
            }
        }
        if (bestPos != -1)
        {
            arr[bestPos].allocated += size;
        }
        printf("memory allocated at position %d\n", bestPos);
    }
    else if (choice == 3)
    {
        int worstPos = -1;
        int worstRem = INT_MIN;
        for (int i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem > worstRem)
                {
                    worstRem = rem;
                    worstPos = i;
                }
            }
        }
        if (worstPos != -1)
        {
            arr[worstPos].allocated += size;
        }
        printf("memory allocated at position %d\n", worstPos);
    }
    else
    {
        printf("invalid choice\n");
    }
    printmem();
}

void memFree(int ptr)
{
    if (ptr <= 10)
    {
        arr[ptr].allocated = 0;
        printf("memory freed at position %d\n", ptr);
    }
    printmem();
}

int main()
{

    for (int i = 0; i < 10; i++)
    {
        arr[i].offset = (i == 0) ? 0 : (arr[i - 1].offset + arr[i - 1].size);
        arr[i].size = sizes[i];
        arr[i].allocated = 0;
    }

    printf("initial memory:\n");
    printmem();

    while (1)
    {
        printf("1. mem check\t2. mem alloc\t3. mem free\n");
        int choice = 0;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("enter size\n");
            int size;
            scanf("%d", &size);
            memCheck(size);
        }
        else if (choice == 2)
        {
            printf("enter size\n");
            int size;
            scanf("%d", &size);
            memAlloc(size);
        }
        else if (choice == 3)
        {
            printf("enter position\n");
            int pos;
            scanf("%d", &pos);
            memFree(pos);
        }
        else
        {
            printf("invalid choice\n");
        }
    }
}