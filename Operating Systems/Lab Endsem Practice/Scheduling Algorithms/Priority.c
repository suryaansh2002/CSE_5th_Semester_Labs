#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// With Preemption: 0 highest priority

struct process
{
    int pid;
    int arrival;
    int burst;
    bool completed;
    int waiting;
    int tat;
    int remaining;
    int lastStop;
    int priority;
};
void print(struct process p[], int n)
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nPID: %d, Arrival Time: %d, Burst Time: %d, Waiting time: %d, Turn around time: %d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].tat);
    }
}
void sort(struct process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (p[i].arrival < p[j].arrival)
            {
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            if (p[i].arrival == p[j].arrival)
            {

                if (p[i].priority < p[j].priority)
                {
                    struct process temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}

int checkProc(struct process p[], int n, int time)
{
    int priority = 999;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (p[i].arrival <= time && p[i].remaining > 0)
        {
            if (p[i].priority < priority)
            {
                priority = p[i].priority;
                index = i;
            }
        }
    }
    return index;
}

int main()
{
    int n;
    printf("Enter the no. of processes:");
    scanf("%d", &n);
    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("\nFor process %d enter: \nArrival time:", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Burst Time:");
        scanf("%d", &p[i].burst);
        printf("Priority:");
        scanf("%d", &p[i].priority);
        p[i].completed = false;
        p[i].waiting = 0;
        p[i].tat = -1;
        p[i].remaining = p[i].burst;
        p[i].lastStop = p[i].arrival;
    }
    sort(p, n);

    int complted_proc = 0;
    int curr_time = 0;
    while (complted_proc != n)
    {

        int procId = checkProc(p, n, curr_time);
        if (procId != -1)
        {
            p[procId].waiting += (curr_time - p[procId].lastStop);
            while (p[procId].remaining > 0)
            {
                printf("Time: %d, Executing: %d\n", curr_time, p[procId].pid);
                p[procId].remaining--;
                curr_time++;
                int newProcId = checkProc(p, n, curr_time);
                if (procId != newProcId)
                {
                    p[procId].lastStop = curr_time;
                    break;
                }
            }
        }
        else
        {
            curr_time++;
        }
        if (p[procId].remaining == 0)
        {
            p[procId].completed = true;
            complted_proc++;
            p[procId].tat = curr_time - p[procId].arrival;
        }
    }

    print(p, n);
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++)
    {
        avg_wt += p[i].waiting;
        avg_tat += p[i].tat;
    }
    avg_wt = avg_wt / n;
    avg_tat = avg_tat / n;
    printf("\nAvg Waiting Time: %f\nAvg Turnaround Time: %f\n", avg_wt, avg_tat);
}