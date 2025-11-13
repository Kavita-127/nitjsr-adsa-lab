/*SET-7
  Q23. Write a function to implement the job sequencing with deadline problem in which each job has integer
deadline and unit processing time. */

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
typedef struct {
    char id;       // Job ID (A, B, C, ...)
    int deadline;  // Deadline of job
    int profit;    // Profit of job
} Job;

// Compare function for sorting jobs in descending order of profit
int compare(const void *a, const void *b) {
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;
    return j2->profit - j1->profit;  // descending by profit
}

// Function to find maximum deadline
int findMaxDeadline(Job jobs[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > max)
            max = jobs[i].deadline;
    return max;
}

// Function to schedule jobs
void jobSequencing(Job jobs[], int n) {
    // Sort jobs by descending profit
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = findMaxDeadline(jobs, n);
    int slot[maxDeadline + 1];  // slots from 1 to maxDeadline
    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = -1;

    int totalProfit = 0;

    // Schedule jobs
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Print results
    printf("\nOptimal Job Sequence: ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != -1)
            printf("%c ", jobs[slot[i]].id);
    }
    printf("\nMaximum Profit: %d\n", totalProfit);
}

int main() {
    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];
    printf("Enter job details in format (ID Deadline Profit):\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobSequencing(jobs, n);

    return 0;
}

