#include<stdio.h>
#include<stdlib.h>

struct frame{
    int value;
    int counter;
};

void printArray(struct frame arr[],int n){
    for(int i=0; i<n;i++){
        printf("%d ", arr[i].value);
    }
    printf("\n");
}
int search(int key, struct frame arr[], int n){
    for(int i=0; i<n;i++){
        if(arr[i].value==key){
            return i;
        }
    }
    return -1;
}

int replaceInd(struct frame arr[], int n){
    int lruCount=9999, lruInd=-1;
    for(int i=0; i<n;i++){
        if(arr[i].counter<lruCount){
            lruCount=arr[i].counter;
            lruInd=i;
        }
    }
    return lruInd;
}

int main(){
    int f, n, hits=0, faults=0;
    printf("Enter the number of frames:");
    scanf("%d", &f);
    printf("Enter the number of references made:");
    scanf("%d", &n);
    struct frame frames[f];
    for(int i=0;i<f;i++){
        frames[i].value=-1;
        frames[i].counter=-1;
    }
    int seq[n];
    printf("Enter sequence of references:");
    for(int i=0; i<n;i++){
        scanf("%d",&seq[i]);
    }
    int count=0;
    for(int i=0;i<n;i++){
        int ele=seq[i];
        printf("\nPage: %d \n", ele);
        int loc=search(ele,frames,f);
        if(loc!=-1){
            printf("Page Hit: ");
            printArray(frames, f);
            hits++;
            frames[loc].counter=count;

        }
        else{
            int vic=replaceInd(frames,f);
            frames[vic].value=ele;
            frames[vic].counter=count;
            printf("Page Fault: ");
            printArray(frames, f);
            faults++;
        }
        count++;
    }
    printf("Page Hits: %d; Page Faults: %d", hits,faults);
}

/*
Sample input:
Frames: 3
References: 20
Sequence: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
*/