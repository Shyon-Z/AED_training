#include <stdio.h>

//////////////////////////////////////////////////
//////////////////////////////////////////////////

int uniquechar(char *s, char counter[][27], char *table, int k);

int main(){

int k=0;
char s[]="fetusdeletus";
char table[]="abcdefghijklmnopqrstuvwxyz";
char counter[2][27];

k=uniquechar(s, counter, table, k);

for(int i=0; i<k; i++){
    printf("\n %c :: %d \n",counter[1][i], counter[0][i]);
    }
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

int uniquechar(char *s, char counter[][27], char *table, int k){

for(int i=0;s[i] !='\0';i++){
    for(int j=0;table[j] !='\0';j++){

        if(s[i]==table[j]){
            counter[0][k]=k+1;
            counter[1][k]=s[i];
            k++;
        }   

    }

}

return k;
}