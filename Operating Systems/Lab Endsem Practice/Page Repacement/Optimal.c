#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int search(int key, int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }
    return -1;
}
int findIndex(int frames[], int f, int seq[], int n, int curr)
{
    int farInd = -1;
    if (search(-1, frames, f) != -1)
    {
        return search(-1, frames, f);
    }
    for (int i = 0; i < f; i++)
    {
        int value = frames[i];
        int flag=0;
        for (int j = curr; j < n; j++)
        {
            if (seq[j] == value)
            {
                flag=1;
                if (j > farInd)
                {
                    farInd = j;
                }
                break;
            }
        }
        if(!flag){
            return i;
        }
    }
    int ind;

    ind = search(seq[farInd], frames, f);
    return ind;
}
int main()
{
    int f, n, hits = 0, faults = 0;
    printf("Enter the number of frames:");
    scanf("%d", &f);
    printf("Enter the number of references made:");
    scanf("%d", &n);
    int frames[f];
    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;
    }
    int seq[n];
    printf("Enter sequence of references:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &seq[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int ele = seq[i];
        printf("\nPage: %d \n", ele);
        if (search(ele, frames, f) != -1)
        {
            printf("Page Hit: ");
            printArray(frames, f);
            hits++;
        }
        else
        {
            int index = findIndex(frames, f, seq, n, i);
            frames[index] = ele;
            printf("Page Fault: ");
            printArray(frames, f);
            faults++;
        }
    }
    printf("Page Hits: %d; Page Faults: %d", hits, faults);
}

/*
Sample input:
Frames: 3
References: 20
Sequence: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
*/