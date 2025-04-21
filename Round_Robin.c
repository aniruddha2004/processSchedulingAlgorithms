#include<stdio.h>
#include<stdbool.h>

struct Process {
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    bool isCompleted;
};

int main() {
    int n, time = 0, tq;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter the arrival time and burst time for the processes\n\n");
    for(int i = 0; i < n; i++) {
        printf("Process %d :\n", (i+1));
        scanf("%d%d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].isCompleted = false;
    }

    printf("Enter the time quantum : ");
    scanf("%d", &tq);

    int done = 0;
    while(done != n) {
        int executed=0;
        for(int i = 0; i < n; i++) {
            if(p[i].arrivalTime <= time && !p[i].isCompleted) {
                if(p[i].remainingTime <= tq) {
                    time+=p[i].remainingTime;
                    p[i].completionTime = time;
                    p[i].remainingTime = 0;
                    p[i].isCompleted = true;
                    p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
                    p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
                    done++;
                }
                else {
                    time+=tq;
                    p[i].remainingTime-=tq;
                }
                executed=1;
            }
        }
        if(!executed)
        time++;
    }

    int totalTAT = 0, totalWT = 0;
    for(int i = 0; i < n; i++){
        printf("\n\nFor process %d\nArrival Time = %d\nBurst Time = %d\nCompletion Time = %d\nTurn Around Time = %d\nWaiting Time = %d\n", (i+1), p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
        totalTAT+=p[i].turnAroundTime;
        totalWT+=p[i].waitingTime;
    }
    printf("\n\nTotal Turn Around Time = %d\n\nTotal Waiting Time = %d", totalTAT, totalWT);
    printf("\n\nAverage Turn Around Time = %.2f\n\nAverage Waiting Time = %.2f", (float)(totalTAT/n), (float)(totalWT/n));
    return 0;
}