#include<stdio.h>


int min(int a,int b){
    return a<b?a:b;

}

//////////////


int module(int* cost, int costsize){
int lc[costsize];
lc[0]=cost[0];
lc[1]=cost[1];

for(int i =2;i<costsize;i++){
    lc[i]=cost[i]+min(lc[i-1], lc[i-2]);
}
    
    return min(lc[costsize -1], lc[costsize -2]);
}

//////////////

int main(){

int n;
n=7;
int cost[n];
int costsize= sizeof(cost)/sizeof(cost[0]);

if (n>=500){
    printf("error");
}

//////////////
for(int i=0;i==n;i++){
    printf("%d \n",cost[n]);
}

int asw=module(cost,costsize);
printf("\n \n \n \n custo minimo = \n %d",asw);
/////////////

return 0;

}