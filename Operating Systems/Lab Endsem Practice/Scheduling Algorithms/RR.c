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
    int remaining;
    int lastStop;
};
void print(struct process p[], int n)
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nPID: %d, Arrival Time: %d, Burst Time: %d, Waiting time: %d, Turn around time: %d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].tat);
    }
}

int main()
{
    int n;
    printf("Enter the no. of processes:");
    scanf("%d", &n);
    printf("Enter Time quantum: ");
    int q;
    scanf("%d", &q);

    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("\nFor process %d enter: \n", i + 1);
        p[i].pid = i + 1;
        printf("Burst Time:");
        scanf("%d", &p[i].burst);
        p[i].completed = false;
        p[i].waiting = 0;
        p[i].tat = -1;
        p[i].remaining = p[i].burst;
        p[i].arrival = 0;
        p[i].lastStop = 0;
    }

    int complted_proc = 0;
    int curr_time = 0;
    while (complted_proc != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (!p[i].completed)
            {
                p[i].waiting += curr_time - p[i].lastStop;
                if (p[i].remaining >= q)
                {
                    p[i].remaining -= q;
                    printf("\nTime: %d to %d: Executing: %d\n", curr_time, curr_time + q, p[i].pid);
                    curr_time += q;
                    p[i].lastStop = curr_time;
                }
                else
                {
                    int r = p[i].remaining;
                    p[i].remaining = 0;
                    printf("Time: %d to %d: Executing: %d", curr_time, curr_time + r, p[i].pid);
                    curr_time += r;
                }
                if (p[i].remaining == 0)
                {
                    p[i].completed = true;
                    complted_proc++;
                    p[i].tat = curr_time - p[i].arrival;
                }
            }
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