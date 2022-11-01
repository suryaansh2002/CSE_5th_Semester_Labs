#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct block
{
    int size;
    bool allocated;
    int availible;
    int pid;
};
void allocate(struct block blocks[], int size, int pid, int n)
{
    int bestDiff = 999999, bestInd = -1;
    for (int i = 0; i < n; i++)
    {
        if (!blocks[i].allocated)
        {
            if (blocks[i].size >= size)
            {
                int diff = blocks[i].size - size;
                if (diff < bestDiff)
                {
                    bestDiff = diff;
                    bestInd = i;
                }
            }
        }
    }
    if (bestInd != -1)
    {
        blocks[bestInd].allocated = true;
        blocks[bestInd].availible = blocks[bestInd].size - size;
        blocks[bestInd].pid = pid;

        printf("\nAllocated Successfully\n \n");
    }
}
void printBlocks(struct block blocks[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Block no. %d, Size: %d, Availible: %d, Process id allocated: %d\n", i + 1, blocks[i].size, blocks[i].availible, blocks[i].pid);
    }
}
int main()
{
    int n;
    printf("Enter the no. of memory blocks:");
    scanf("%d", &n);
    struct block blocks[n];
    printf("Enter the sizes of the %d blocks: ", n);
    for (int i = 0; i < n; i++)
    {
        int s;
        scanf("%d", &s);
        blocks[i].size = s;
        blocks[i].availible = s;
        blocks[i].pid = -1;
    }
    while (1)
    {
        printf("\nChoose an option:\n1.Allocate Mem 2.Free Memory 3. Print Memory 4. Exit\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter Process id:");
            int pid;
            scanf("%d", &pid);
            printf("Enter Size of block: ");
            int size;
            scanf("%d", &size);
            allocate(blocks, size, pid, n);
        }
        else if (choice == 2)
        {
            printf("Enter block no. to free: (1 - %d)", n);
            int num;
            scanf("%d", &num);
            blocks[num - 1].allocated = false;
            blocks[num - 1].availible = blocks[num - 1].size;
            blocks[num - 1].pid = -1;
            printf("\nMemory cleared successfully\n\n");
        }
        else if (choice == 3)
        {
            printBlocks(blocks, n);
        }
        else if (choice == 4)
        {
            exit(0);
        }
        else
        {
            printf("Error input, please try again!\n");
        }
    }
}