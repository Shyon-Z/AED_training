#include <stdio.h>
#include <stdlib.h>
////////////////////////////////////////////////////
///////////////////////////////////////////////////
/*
Érick Machado De Freitas  18200262

The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0 and 1 
respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.

The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a stack. At each step:

-If the student at the front of the queue prefers the sandwich on the top of the stack, they will take it and leave the queue.

-Otherwise, they will leave it and go to the queue's end.

-This continues until none of the queue students want to take the top sandwich and are thus unable to eat

You are given two integer arrays students and sandwiches where sandwiches[i] is the type of the i​​​​​​th sandwich in the stack 
(i = 0 is the top of the stack) and students[j] is the preference of the j​​​​​​th student in the initial queue 
(j = 0 is the front of the queue). Return the number of students that are unable to eat.

*/
////////////////////////////////////////////////////
////////////////////////////////////////////////////


int ArrayShift(int sandwich[], int students[],int size);

int main(){


  int sandwich[]={0,1,0,1};
  int students[]={1,1,0,0};
  int size= sizeof(students)/sizeof(students[0]);
  int studentsfeeded= 0;

//////////////////////

for(int i=0;i < size;i++){
    if(sandwich[0]==students[0]){
    
        for (int k = 0 ; k < size -1; k++){
            students[k] = students[k+1];
            sandwich[k] = sandwich[k+1];
        }
            studentsfeeded++;
            printf("Estudande pega o lanche e sai da fila\n");

        
    }
    else{
        ArrayShift(sandwich, students, size);
        printf("Estutante volta ao final da fila\n");
    }
}

if(studentsfeeded == size){
    printf("\nTodos os estudantes receberam lanche \n");
}else{
    printf("\nAlguns estudantes ficarão sem lanche\n");
}
//////////////////////

    
    return 0;
}

////////////////////////////////////////////////////


int ArrayShift(int sandwich[], int students[], int size) {
    int tempStudents = students[0];
    int tempSandwich = sandwich[0];

    for (int i = 0; i < size - 1; i++) {
        students[i] = students[i + 1];
        sandwich[i] = sandwich[i + 1];
    }

    students[size - 1] = tempStudents;
    sandwich[size - 1] = tempSandwich;

    return 0;
}