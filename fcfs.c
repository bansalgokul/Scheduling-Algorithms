#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Process
{
    int pid;
    int arrival;
    int burst;
    int turnAround;
    int waiting;
    int response;
    int start;
    int completion;
};

typedef struct Process process;

void sortArrival(process arr[], int n)
{
    int i, j;
    process temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].arrival > arr[j + 1].arrival)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void sortId(process arr[], int n)
{
    int i, j;
    process temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].pid > arr[j + 1].pid)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    process arr[100];
    int turnAround = 0;
    int waiting = 0;
    int response = 0;
    float averageTurnAround;
    float averageWaiting;
    float averageResponse;

    printf("Enter number of processes ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time of process %d", i + 1);
        scanf("%d", &arr[i].arrival);
        printf("Enter burst time of process %d", i + 1);
        scanf("%d", &arr[i].burst);
        arr[i].pid = i + 1;
        printf("\n");
    }

    sortArrival(arr, n);

    for (int i = 0; i < n; i++)
    {
        arr[i].start = (i == 0) ? arr[i].arrival : fmax(arr[i - 1].completion, arr[i].arrival);
        arr[i].completion = arr[i].start + arr[i].burst;
        arr[i].turnAround = arr[i].completion - arr[i].arrival;
        arr[i].waiting = arr[i].turnAround - arr[i].burst;
        arr[i].response = arr[i].start - arr[i].arrival;

        turnAround += arr[i].turnAround;
        waiting += arr[i].waiting;
        response += arr[i].response;
    }

    averageTurnAround = (float)turnAround / n;
    averageWaiting = (float)waiting / n;
    averageResponse = (float)response / n;

    sortId(arr, n);

    printf("Average Turnaround time = %.2f", averageTurnAround);
    printf("Average Waiting time = %.2f", averageWaiting);
    printf("Average Response time = %.2f", averageResponse);
}