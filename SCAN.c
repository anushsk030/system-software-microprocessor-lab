
/*#include<stdio.h>
#include<stdlib.h>
void main(){
    int no_req,size,initial,HeadMovement=0;
    printf("Enter the no. of requests: ");
    scanf("%d",&no_req);
    int req[20];
    printf("Enter the size: ");
    scanf("%d",&size);
    printf("enter the requests: ");
    for(int i=0;i<no_req;i++){
        scanf("%d",&req[i]);
    }

      printf("enter the initial head position: ");
      scanf("%d",&initial);
     for(int i=0;i<no_req;i++){
        for(int j=i+1;j<no_req;j++){
            if(req[j]<req[i]){
                int temp=req[j];
                req[j]=req[i];
                req[i]=temp;
            }
        }
     }
     int index=0;
     while(index<no_req && req[index]<=initial){
        index++;
     }
     for(int i=index-1;i>=0;i--){
        HeadMovement+=abs(req[i]-initial);
        initial=req[i];
     }
     HeadMovement+=abs(req[0]-0);
     initial=0;
     for(int i=0;i<no_req;i++){
        HeadMovement+=abs(req[i]-initial);
        initial=req[i];
     }
     printf("Head movement %d",HeadMovement);
}

*/

#include <stdio.h>
#include <stdlib.h>

void main()
{
   int head,limit,distance,seektime = 0 ,size,direction;

   printf("Enter initial head position\n");
   scanf("%d",&head);

   printf("Enter number of requests\n");
   scanf("%d",&limit);
   int req[limit];

   printf("Enter requests:\n");
   for(int i=0; i< limit ;i++)
    scanf("%d",&req[i]);

    printf("\nEnter total disk size : ");
    scanf("%d",&size);

    printf("\nEnter the head movement direction(1 for high & 0 for low) : ");
    scanf("%d",&direction);

    //Sorting the req in asc
    for(int i=0 ;i < limit ;i++){
        for(int j=i+1; j<limit ;j++){
            if(req[i]>req[j]){
                int temp = req[i];
                req[i]=req[j];
                req[j]=temp;
            }
        }
    }

    if(direction==1){
        seektime += size - 1 - head;
        if (req[0] < head){
            seektime += size - 1 - req[0];
        }
    }
    else{
        seektime += head;
        if (req[limit-1] > head){
            seektime += req[limit-1];
        }
    }
    printf("Total Head Movement is %d\n",seektime);
}
