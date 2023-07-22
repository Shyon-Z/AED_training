#include <stdio.h>

int main() {
    int v[6];
    int k;

    v[0]=1;
    v[1]=0;
    v[2]=5;
    v[3]=-2;
    v[4]=-5;
    v[5]=7;

    k= v[0]+v[1]+v[5];

    printf("%d \n",k);

    v[4]=100;

    printf("%d \n",v[0]);
    printf("%d \n",v[1]);
    printf("%d \n",v[2]);
    printf("%d \n",v[3]);
    printf("%d \n",v[4]);
    printf("%d \n",v[5]);

return 0;
};
