#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process
{
    int pid;
    int arrival;
    int burst;
    bool completed;
    int waiting;
    int tat;
};
void print(struct process p[], int n){
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nPID: %d, Arrival Time: %d, Burst Time: %d, Waiting time: %d, Turn around time: %d\n", p[i].pid,p[i].arrival,p[i].burst,p[i].waiting,p[i].tat);
    }
    
}
void sort(struct process p[], int n){
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++){
            if(p[i].arrival<p[j].arrival){
                struct process temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}
int main()
{
    int n;
    printf("Enter the no. of processes:");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0; i<n; i++)
    {   
        p[i].pid=i+1;
        printf("\nFor process %d enter: \nArrival time:", i+1);
        scanf("%d",&p[i].arrival);
        printf("Burst Time:");
        scanf("%d", &p[i].burst);
        p[i].completed=false;
        p[i].waiting=-1;

    }
    sort(p,n);
    int complted_proc=0;
    int curr_time=0;
    while(complted_proc!=n){
        for(int i=0; i<n;i++){
            if(!p[i].completed){
                p[i].waiting=curr_time - p[i].arrival;
                curr_time+=p[i].burst;
                p[i].completed=true;
                p[i].tat=curr_time-p[i].arrival;
                complted_proc++;
            }
        }
    }
    print(p,n);
    int avg_wt=0, avg_tat=0;
    for(int i=0; i<n;i++){
        avg_wt+=p[i].waiting;
        avg_tat+=p[i].tat;
    }
    avg_wt=avg_wt/n;
    avg_tat=avg_tat/n;
    printf("\nAvg Waiting Time: %d\nAvg Turnaround Time: %d\n", avg_wt,avg_tat);
}