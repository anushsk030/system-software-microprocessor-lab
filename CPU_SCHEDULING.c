#include <stdio.h>

void fcfs() {
    printf("--------FCFS Scheduling--------\n");
    int n;
    printf("Enter the no. of processes\n");
    scanf("%d", &n);
    int p[n], bt[n], wt[n], tat[n], tot_wt = 0, tot_tat = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter the burst time of process %d:\n", i);
        scanf("%d", &bt[i]);
        p[i] = i;
    }

    wt[0] = 0; 
    tat[0] = bt[0]; 
    tot_tat += tat[0]; 

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1]; 
        tot_wt += wt[i]; 
        tat[i] = tat[i - 1] + bt[i]; 
        tot_tat += tat[i]; 
    }

    float avg_wt = (float)tot_wt / n; 
    float avg_tat = (float)tot_tat / n;

    printf("Process\t\tBT\t\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t%d\t\t", p[i], bt[i], wt[i], tat[i]);
        printf("\n");
    }
    printf("Total WT: %d  Avg WT: %f\n", tot_wt, avg_wt);
    printf("Total TAT: %d  Avg TAT: %f\n", tot_tat, avg_tat);
    printf("------------------------------------\n");
    printf("Gantt Chart  :\n");
    for (int i = 0; i < n; i++) {
        printf("|P%d  |", p[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d    ", wt[i]);
    }
    printf("%d", tat[n - 1]);
    printf("\n");
}

void sjf() {
    printf("--------------SJF Scheduling----------------\n");
    int n;
    printf("Enter the no. of processes\n");
    scanf("%d", &n);
    int p[n], bt[n], wt[n], tat[n], tot_wt = 0, tot_tat = 0;
    int temp1, temp2;

    for (int i = 0; i < n; i++) {
        printf("Enter the burst time of process %d:\n", i);
        scanf("%d", &bt[i]);
        p[i] = i;
    }

   
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                
                temp1 = bt[i];
                bt[i] = bt[j];
                bt[j] = temp1;

                
                temp2 = p[i];
                p[i] = p[j];
                p[j] = temp2;
            }
        }
    }

    wt[0] = 0;
    tat[0] = bt[0]; 
    tot_tat += tat[0]; 

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1]; 
        tot_wt += wt[i]; 
        tat[i] = tat[i - 1] + bt[i]; 
        tot_tat += tat[i]; 
    }

    float avg_wt = (float)tot_wt / n; 
    float avg_tat = (float)tot_tat / n; 

    printf("Process\t\tBT\t\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t%d\t\t", p[i], bt[i], wt[i], tat[i]);
        printf("\n");
    }
    printf("Total WT: %d  Avg WT: %f\n", tot_wt, avg_wt);
    printf("Total TAT: %d  Avg TAT: %f\n", tot_tat, avg_tat);
    printf("------------------------------------\n");
    printf("Gantt Chart  :\n");
    for (int i = 0; i < n; i++) {
        printf("|P%d  |", p[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
    printf("%d    ", wt[i]);
    }
 printf("%d", tat[n - 1]);
}

void priority() {
    printf("--------------PRIORITY Scheduling---------------\n");
    int n;
    printf("Enter the no. of processes\n");
    scanf("%d", &n);
    int p[n], bt[n], wt[n], tat[n], tot_wt = 0, tot_tat = 0, pri[n];
    int temp1, temp2, temp3;

    for (int i = 0; i < n; i++) {
        printf("Enter the burst time of process %d:\n", i);
        scanf("%d", &bt[i]);
        printf("Enter the priority of process %d:\n", i);
        scanf("%d", &pri[i]);
        p[i] = i;
       }

    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pri[i] > pri[j]) {
               
                temp3 = pri[i];
                pri[i] = pri[j];
                pri[j] = temp3;

                
                temp1 = bt[i];
                bt[i] = bt[j];
                bt[j] = temp1;

                temp2 = p[i];
                p[i] = p[j];
                p[j] = temp2;
            }
        }
    }

    wt[0] = 0; 
    tat[0] = bt[0]; 
    tot_tat += tat[0]; 

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tot_wt += wt[i]; 
        tat[i] = tat[i - 1] + bt[i]; 
        tot_tat += tat[i]; 
    }

    float avg_wt = (float)tot_wt / n; 
    float avg_tat = (float)tot_tat / n; 

    printf("Process\t\tBT\t\tWT\tTAT\t\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t%d\t\t%d", p[i], bt[i], wt[i], tat[i], pri[i]);
        printf("\n");
    }
    printf("Total WT: %d  Avg WT: %f\n", tot_wt, avg_wt);
    printf("Total TAT: %d  Avg TAT: %f\n", tot_tat, avg_tat);
    printf("------------------------------------\n");
    printf("Gantt Chart  :\n");
    for (int i = 0; i < n; i++) {
        printf("|P%d  |", p[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d    ", wt[i]);
    }
    printf("%d", tat[n - 1]);
}

int main() {
  int choice;
  do{
  printf("\n");
        printf("Enter the Choice 1.FCFS   2.SJF    3.PRIORITY  4.Round Robin 5.Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fcfs();
                break;
            case 2:
                sjf();
                break;
            case 3:
                priority();
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
   } while (choice != 5);
    return 0;
}
