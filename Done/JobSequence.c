#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INF 99
typedef struct Job
{
    int id, p, d;
} Job;
int n;

Job jobs[100];
int maxD = INT_MIN;

void Sort()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (jobs[j].p < jobs[j + 1].p)
            {
                Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}

void JobSequence()
{
    Sort();

    int jobseq[maxD + 1];
    int totalProfit = 0;
    int jobsDone = 0;

    for (int i = 0; i <= maxD; i++)
    {
        jobseq[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int d = jobs[i].d;

        for (int j = d; j >= 1; j--)
        {
            if (jobseq[j] == 0)
            {
                jobseq[j] = jobs[i].id;
                totalProfit += jobs[i].p;
                jobsDone++;
                break;
            }
        }
    }

    printf("\nJob Sequence:\n");
    for (int i = 1; i <= maxD; i++)
    {
        if (jobseq[i] != 0)
        {
            printf("Slot %d : Job %d\n", i, jobseq[i]);
        }
    }

    printf("Jobs Done : %d\n", jobsDone);
    printf("Total Profit : %d\n", totalProfit);
}

int main()
{
    printf("Enter the number of Jobs : ");
    scanf("%d", &n);
    printf("Enter the Id Profit and Deadline");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &jobs[i].id, &jobs[i].d, &jobs[i].p);
        if (jobs[i].d > maxD)
            maxD = jobs[i].d;
    }
    JobSequence();
}
