#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, ct, tat, wt;
} p[25];
struct process temp;
int i,n;
void calculate_times(int n);
void print_gantt_chart(int n);
void print_table(int n);
void avg_tat_wt(int n);

int main() {
    

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    printf("Enter the Arrival time for each process (in ms):\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i;
        printf("P[%d]: ", i);
        scanf("%d", &p[i].at);
        p[i].wt = p[i].tat = 0;
    }

    printf("Enter the Burst time for each process (in ms):\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]: ", i);
        scanf("%d", &p[i].bt);
    }

    // Sort by arrival time
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                 temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate times
    calculate_times(n);

    // Print results
    printf("\n");
    print_gantt_chart(n);
    printf("\n");
    print_table(n);
    printf("\n");
    avg_tat_wt(n);

    return 0;
}

void calculate_times(int n) {
    p[0].ct = p[0].at + p[0].bt;
    p[0].tat = p[0].ct - p[0].at;
    p[0].wt = 0;

    for (i = 1; i < n; i++) {
        p[i].ct = p[i - 1].ct + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void print_gantt_chart(int n) {
    printf("GANTT CHART\n");

    for ( i = 0; i < n; i++) {
        printf("---------");
    }
    printf("-\n");

    for ( i = 0; i < n; i++) {
        printf("| P[%d]\t ", p[i].pid);
    }
    printf("|\n");

    for ( i = 0; i < n; i++) {
        printf("---------");
    }
    printf("-\n");

    printf("%d\t", p[0].at);
    for ( i = 0; i < n; i++) {
        printf(" %d\t", p[i].ct);
    }
    printf("\n");
}

void print_table(int n) {
    printf("--------------------------------------------------------------------------------\n");
    printf("| PID | ARRIVAL TIME | BURST TIME | COMPLETION TIME | TURNAROUND TIME | WAITING TIME |\n");
    printf("--------------------------------------------------------------------------------\n");

    for ( i = 0; i < n; i++) {
        printf("| %3d | %12d | %10d | %15d | %15d | %12d |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("--------------------------------------------------------------------------------\n");
}

void avg_tat_wt(int n) {
    int sum_wt = 0, sum_tat = 0;
    float average_wt, average_tat;

    for ( i = 0; i < n; i++) {
        sum_wt += p[i].wt;
        sum_tat += p[i].tat;
    }

    average_wt = (float)sum_wt / n;
    average_tat = (float)sum_tat / n;

    printf("Average Waiting Time = %.2f ms\n", average_wt);
    printf("Average Turnaround Time = %.2f ms\n", average_tat);
}