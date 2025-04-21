#include<stdio.h>
#include<stdbool.h>

struct Process {
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    bool isCompleted;
    int priority;
};

int main() {
    int n, time = 0;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    struct Process p[n];
    struct Process r[n];
    printf("Enter the arrival time, burst time and priority for the processes\n\n");
    for(int i = 0; i < n; i++) {
        printf("Process %d :\n", (i+1));
        scanf("%d%d%d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
        p[i].isCompleted = false;
    }

    for(int i = 0; i < n-1; i++) {
        int s = i;
        for(int j = i+1; j < n; j++) {
            if(p[s].arrivalTime > p[j].arrivalTime) {
                s = j;
            }
        }
        struct Process temp = p[i];
        p[i] = p[s];
        p[s] = temp;
    }

    int done = 0, totalTAT = 0, totalWT = 0, count = 0;
    while(done != n){
        int maxPriority = 1e9;
        int idx = -1;
        for(int i = 0; i < n; i++){
            if(p[i].arrivalTime <= time && !p[i].isCompleted){
                if(p[i].priority < maxPriority) {
                    maxPriority = p[i].priority;
                    idx = i;
                }
            }
        }
        if(idx == -1) {
            time++;
        }
        else {
            time+=p[idx].burstTime;
            p[idx].completionTime = time;
            p[idx].turnAroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnAroundTime - p[idx].burstTime;
            p[idx].isCompleted=true;
            done++;
            totalTAT += p[idx].turnAroundTime;
            totalWT += p[idx].waitingTime;
            r[count++] = p[idx];
        }
    }
    for(int i = 0; i < n; i++){
        printf("\n\nFor process %d\nPriority = %d\nArrival Time = %d\nBurst Time = %d\nCompletion Time = %d\nTurn Around Time = %d\nWaiting Time = %d\n", (i+1), r[i].priority, r[i].arrivalTime, r[i].burstTime, r[i].completionTime, r[i].turnAroundTime, r[i].waitingTime);
    }
    printf("\n\nTotal Turn Around Time = %d\n\nTotal Waiting Time = %d", totalTAT, totalWT);
    printf("\n\nAverage Turn Around Time = %.2f\n\nAverage Waiting Time = %.2f", (float)(totalTAT/n), (float)(totalWT/n));
    return 0;
}