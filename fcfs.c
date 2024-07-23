#include<stdio.h>
void main(){
     int n;
     printf("Enter the no. of processes\n");
     scanf("%d",&n);
     int p[n],bt[n],wt[n],tat[n],tot_wt,tot_tat;
    
     for(int i=0;i<n;i++){
      printf("Enter the burst time of process %d:\n",i);
       scanf("%d",&bt[i]);
       p[i]=i;
         
     }
     
     
     wt[0]=0;
     tat[0]=bt[0];
     for(int i=1;i<n;i++){
             wt[i]=wt[i-1]+bt[i-1];
             tot_wt=tot_wt+wt[i];
             tat[i]=tat[i-1]+bt[i];
             tot_tat=tot_tat+tat[i];
             }
             tot_tat=tot_tat+tat[0];
             float avg_wt=(float)tot_wt/n;
             float avg_tat=(float)tot_tat/n;
       printf("Process\t\tBT\t\tWT\tTAT\n");
       for(int i=0;i<n;i++){
         printf("P%d\t\t%d\t\t%d\t%d\t\t",p[i],bt[i],wt[i],tat[i]);
         printf("\n");
         }
         printf("Total wt %d  Avg wt %f\n",tot_wt,avg_wt);
         printf("Total tat %d Avg tat %f\n",tot_tat,avg_tat);
         printf("------------------------------------\n");
         printf("Gant Chart  :\n");
         for(int i=0;i<n;i++){
             printf("|P%d  |",p[i]);
             }
             printf("\n");
        for(int i=0;i<n;i++){
             printf("%d    ",wt[i]);
             }
         printf("%d",tat[n-1]);
}
     
