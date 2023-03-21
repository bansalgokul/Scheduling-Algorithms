#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
    int val;
    struct node *next;
} node_t;

void enqueue(node_t **head, int val)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
        return;

    new_node->val = val;
    new_node->next = *head;

    *head = new_node;
}

int dequeue(node_t **head)
{
    node_t *current, *prev = NULL;
    int retval = -1;

    if (*head == NULL)
        return -1;

    current = *head;
    while (current->next != NULL)
    {
        prev = current;
        current = current->next;
    }

    retval = current->val;
    free(current);

    if (prev)
        prev->next = NULL;
    else
        *head = NULL;

    return retval;
}
int empty(node_t **head)
{
    if (*head == NULL)
    {
        return 1;
    }
    return 0;
}

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

int main()
{
    int n;
    int tq;
    process arr[100];
    int turnAround = 0;
    int waiting = 0;
    int response = 0;
    float averageTurnAround;
    float averageWaiting;
    float averageResponse;
    int burstRemaining[100];
    int idx;
    int currentTime = 0;
    node_t *head = NULL;
    int completed = 0;
    int mark[100] = {0};

    printf("Enter number of processes ");
    scanf("%d", &n);
    printf("Enter time quantum");
    scanf("%d", &tq);

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time of process %d ", i + 1);
        scanf("%d", &arr[i].arrival);
        printf("Enter burst time of process %d ", i + 1);
        scanf("%d", &arr[i].burst);
        burstRemaining[i] = arr[i].burst;
        arr[i].pid = i + 1;
        printf("\n");
    }

    sortArrival(arr, n);

    int i = 0;
    enqueue(&head, 0);
    mark[0] = 1;

    while (completed != n)
    {
        i = dequeue(&head);

        if (burstRemaining[i] == arr[i].burst)
        {
            arr[i].start = fmax(currentTime, arr[i].arrival);
            currentTime = arr[i].start;
        }

        if (burstRemaining[i] > tq)
        {
            burstRemaining[i] -= tq;
            currentTime += tq;
            enqueue(&head, i);
        }
        else
        {
            currentTime += burstRemaining[i];
            burstRemaining[i] = 0;
            completed++;

            arr[i].completion = currentTime;
            arr[i].turnAround = arr[i].completion - arr[i].arrival;
            arr[i].waiting = arr[i].turnAround - arr[i].burst;
            arr[i].response = arr[i].start - arr[i].arrival;

            turnAround += arr[i].turnAround;
            waiting += arr[i].waiting;
            response += arr[i].response;
        }

        for (int j = 1; j < n; j++)
        {
            if (burstRemaining[j] > 0 && arr[j].arrival <= currentTime && mark[j] == 0)
            {
                enqueue(&head, j);
                mark[j] = 1;
            }
        }

        if (burstRemaining[i] > 0)
        {
            enqueue(&head, i);
        }

        if (empty(&head))
        {
            for (int j = 1; j < n; j++)
            {
                if (burstRemaining[j] > 0)
                {
                    enqueue(&head, j);
                    mark[j] = 1;
                    break;
                }
            }
        }
    }

    averageTurnAround = (float)turnAround / n;
    averageWaiting = (float)waiting / n;
    averageResponse = (float)response / n;

    printf("Average Turnaround time = %.2f", averageTurnAround);
    printf("Average Waiting time = %.2f", averageWaiting);
    printf("Average Response time = %.2f", averageResponse);
}
