#include <stdio.h>
#include <stdlib.h>

struct matrix {
    struct matrix* right;
    struct matrix* below;
    int line;
    int column;
    float info;
};

//////////////////////////////////////////////////////////////////

void matrix_print(struct matrix* head, int rows, int cols){

struct matrix* rowPtr = head;

    for (int i = 0; i < rows; i++){
        struct matrix* colPtr = rowPtr->right;

        for (int j = 0; j < cols; j++) {
            if (colPtr != NULL && colPtr->line == i && colPtr->column == j){
                printf("%.1f ", colPtr->info);
                colPtr = colPtr->right;
            }else{
                printf(" 0.0 ");
            }
        }

        printf("\n");
        rowPtr = rowPtr->below;
    }
}

//////////////////////////////////////////////////////////////////

void matrix_create(struct matrix** head, int rows, int cols) {
    *head = (struct matrix*)malloc(sizeof(struct matrix));
    (*head)->right = *head;
    (*head)->below = *head;
    (*head)->line = -1;
    (*head)->column = -1;
    (*head)->info = 0.0;

    struct matrix* current_row = *head;

    for (int i = 0; i < rows; i++) {
        struct matrix* current_col = current_row;

        for (int j = 0; j < cols; j++) {
            current_col->right = (struct matrix*)malloc(sizeof(struct matrix));
            current_col = current_col->right;
            current_col->right = current_row;
            current_col->below = NULL;
            current_col->line = i;
            current_col->column = j;
            current_col->info = 0.0;
        }

        current_row->below = (struct matrix*)malloc(sizeof(struct matrix));
        current_row = current_row->below;
        current_row->right = *head;
        current_row->below = NULL;
        current_row->line = i + 1;
        current_row->column = -1;
        current_row->info = 0.0;
    }
}

//////////////////////////////////////////////////////////////////

void matrix_destroy(struct matrix** head) {
    struct matrix* current_row = *head;

    while (current_row != NULL) {
        struct matrix* current_col = current_row->right;
        while (current_col != current_row) {
            struct matrix* temp = current_col;
            current_col = current_col->right;
            free(temp);
        }

        struct matrix* temp = current_row;
        current_row = current_row->below;
        free(temp);
    }

    *head = NULL;
}

//////////////////////////////////////////////////////////////////

void matrix_add(struct matrix* A, struct matrix* B, int rows, int cols) {
    struct matrix* temp = NULL;
    matrix_create(&temp, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            struct matrix* currentA = A->below;
            struct matrix* currentB = B->below;
            while (currentA->line < i) currentA = currentA->below;
            while (currentB->line < i) currentB = currentB->below;
            struct matrix* currentACol = currentA->right;
            struct matrix* currentBCol = currentB->right;
            while (currentACol->column < j) currentACol = currentACol->right;
            while (currentBCol->column < j) currentBCol = currentBCol->right;

            struct matrix* currentTemp = temp->below;
            while (currentTemp->line < i) currentTemp = currentTemp->below;
            struct matrix* currentTempCol = currentTemp->right;
            while (currentTempCol->column < j) currentTempCol = currentTempCol->right;

            currentTempCol->info = currentACol->info + currentBCol->info;
        }
    }

    printf("Matrix A + B:\n");
    matrix_print(temp, rows, cols);
    matrix_destroy(&temp);
}

//////////////////////////////////////////////////////////////////

void matrix_multiply(struct matrix* A, struct matrix* B, int rows, int cols) {
    struct matrix* temp = NULL;
    matrix_create(&temp, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float sum = 0.0;
            struct matrix* currentA = A->below;
            while (currentA->line < i) currentA = currentA->below;
            struct matrix* currentACol = currentA->right;
            struct matrix* currentB = B->right;
            while (currentB->column < j) currentB = currentB->right;

            struct matrix* currentTemp = temp->below;
            while (currentTemp->line < i) currentTemp = currentTemp->below;
            struct matrix* currentTempCol = currentTemp->right;
            while (currentTempCol->column < j) currentTempCol = currentTempCol->right;

            while (currentACol->column < cols) {
                sum += (currentACol->info) * (currentB->info);
                currentACol = currentACol->right;
                currentB = currentB->below;
            }

            currentTempCol->info = sum;
        }
    }

    printf("Matrix A * B:\n");
    matrix_print(temp, rows, cols);
    matrix_destroy(&temp);
}

//////////////////////////////////////////////////////////////////

float matrix_getelem(struct matrix* A, int row, int col) {
    struct matrix* current = A;
    while (current->line < row) current = current->below;
    while (current->column < col) current = current->right;

    return current->info;
}

//////////////////////////////////////////////////////////////////

void matrix_setelem(struct matrix* A, int row, int col, float value) {
    struct matrix* current = A;
    while (current->line < row) current = current->below;
    while (current->column < col) current = current->right;

    current->info = value;
}

//////////////////////////////////////////////////////////////////

void matrix_transpose(struct matrix* A, int rows, int cols) {
    struct matrix* temp = NULL;
    matrix_create(&temp, cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float value = matrix_getelem(A, i, j);
            matrix_setelem(temp, j, i, value);
        }
    }

    printf("Transposed Matrix A:\n");
    matrix_print(temp, cols, rows);
    matrix_destroy(&temp);
}

//////////////////////////////////////////////////////////////////

int main(){

int rows, cols;

/////////////////////////////////

struct matrix* A = NULL;
matrix_create(&A, 4, 4);

matrix_setelem(A, 0, 0, 50);
matrix_setelem(A, 0, 2, 10);
matrix_setelem(A, 0, 3, 20);
matrix_setelem(A, 1, 1, 10.5);
matrix_setelem(A, 3, 0, -30);
matrix_setelem(A, 3, 2, -65);
matrix_setelem(A, 3, 3, 5);

/////////////////////////////////

struct matrix* B = NULL;
matrix_create(&B, 4, 4);

matrix_setelem(B, 0, 0, 50);
matrix_setelem(B, 0, 1, 30);
matrix_setelem(B, 1, 0, 10);
matrix_setelem(B, 1, 2, -20);
matrix_setelem(B, 3, 3, -5);

/////////////////////////////////

struct matrix* C = NULL;
matrix_create(&C, 5, 5);

matrix_setelem(C, 0, 0, 1);
matrix_setelem(C, 0, 3, 6);
matrix_setelem(C, 1, 1, 10.5);
matrix_setelem(C, 2, 2, 0.015);
matrix_setelem(C, 3, 1, 250.5);
matrix_setelem(C, 3, 3, -280);
matrix_setelem(C, 3, 4, -33.32);
matrix_setelem(C, 4, 4, 12);

/////////////////////////////////

struct matrix* D = NULL;
matrix_create(&D, 5, 4);

matrix_setelem(D, 0, 0, 1);
matrix_setelem(D, 1, 1, 10.5);
matrix_setelem(D, 2, 2, 0.3);
matrix_setelem(D, 3, 1, 100);
matrix_setelem(D, 3, 3, 30);
matrix_setelem(D, 4, 3, 1);

/////////////////////////////////

    printf("Numero de linhas: \n");
    scanf("%d", &rows);

    printf("Numero de colunas: \n");
    scanf("%d", &cols);

    struct matrix* head = NULL;
    matrix_create(&head, rows, cols);

/////////////////////////////////

char choice_update;
do {
    int row, col;
    float value;

    printf("\n Digite qual linha, coluna e o valor (ex: 0 1 3.5): ");
    scanf("%d %d %f", &row, &col, &value);

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        struct matrix* current = head->below;
        for (int i = 0; i < row; i++) {
            current = current->below;
        }
        struct matrix* current_col = current->right;
        for (int j = 0; j < col; j++) {
            current_col = current_col->right;
        }
        current_col->info = value;
    } else {
        printf("Coordenadas inválidas.\n");
    }

    printf("Inserção de %.1f em (%d, %d):\n", value, row, col);
    matrix_print(head, rows, cols);

    printf("\nGostaria de adicionar outro número? (y/n): ");
    scanf(" %c", &choice_update);
} while (choice_update == 'y' || choice_update == 'Y');

/////////////////////////////////
/////////////////////////////////

    printf("Matriz atualizada com %d linhas e %d colunas \n", rows, cols);
    matrix_print(head, rows, cols);

    int choice;
    printf("Escolha uma operacao:\n");
    printf("1. Adicao\n");
    printf("2. Multiplicacao\n");
    printf("3. Transposicao\n");
    scanf("%d", &choice);

     if (choice == 1) {
        int matrixChoice;
        printf("Escolha qual matriz sera adicionada (A=1, B=2, C=3, D=4): ");
        scanf("%d", &matrixChoice);

        if (matrixChoice == 1) {
    matrix_add(head, A, rows, cols);
    printf("Result of Matrix A + B:\n");
    matrix_print(A, rows, cols); 
} else if (matrixChoice == 2) {
    matrix_add(head, B, rows, cols);
    printf("Result of Matrix A + B:\n");
    matrix_print(B, rows, cols);
} else if (matrixChoice == 3) {
    matrix_add(head, C, rows, cols);
    printf("Result of Matrix A + C:\n");
    matrix_print(C, rows, cols); 
} else if (matrixChoice == 4) {
    matrix_add(head, D, rows, cols);
    printf("Result of Matrix A + D:\n");
    matrix_print(D, rows, cols);
} else {
    printf("Escolha invalida.\n");
}
}

/////////////////////////////////
/////////////////////////////////

else if (choice == 2) {

        int matrixChoice;
        printf("Escolha qual matriz sera multiplicada (A=1, B=2, C=3, D=4): ");
        scanf("%d", &matrixChoice);

if (matrixChoice == 1) {
    matrix_multiply(head, A, rows, cols);
    printf("Result of Matrix A + B:\n");
    matrix_print(A, rows, cols);
} else if (matrixChoice == 2) {
    matrix_multiply(head, B, rows, cols);
    printf("Result of Matrix A + B:\n");
    matrix_print(B, rows, cols);
} else if (matrixChoice == 3) {
    matrix_multiply(head, C, rows, cols);
    printf("Result of Matrix A + C:\n");
    matrix_print(C, rows, cols);
} else if (matrixChoice == 4) {
    matrix_multiply(head, D, rows, cols);
    printf("Result of Matrix A + D:\n");
    matrix_print(D, rows, cols); 
} else {
    printf("Escolha invalida.\n");
}
    
/////////////////////////////////
/////////////////////////////////

}
 else if (choice == 3) {

        int matrixChoice;
        printf("Escolha qual matriz sera transposta (A=1, B=2, C=3, D=4): ");
        scanf("%d", &matrixChoice);

if (matrixChoice == 1) {
    matrix_transpose(A, rows, cols);
    printf("Transposed Matrix A:\n");
    matrix_print(A, cols, rows); 
} else if (matrixChoice == 2) {
    matrix_transpose(B, rows, cols);
    printf("Transposed Matrix B:\n");
    matrix_print(B, cols, rows);
} else if (matrixChoice == 3) {
    matrix_transpose(C, rows, cols);
    printf("Transposed Matrix C:\n");
    matrix_print(C, cols, rows);
} else if (matrixChoice == 4) {
    matrix_transpose(D, rows, cols);
    printf("Transposed Matrix D:\n");
    matrix_print(D, cols, rows); 
} 

/////////////////////////////////
/////////////////////////////////

    int row, col;
    printf("Digite a linha e coluna para obter um elemento: ");
    scanf("%d %d", &row, &col);
    float elem = matrix_getelem(head, row, col);
    printf("Elemento em (%d, %d): %.1f\n", row, col, elem);

    printf("Digite a linha, coluna e valor para definir um elemento: ");
    scanf("%d %d %f", &row, &col, &elem);
    matrix_setelem(head, row, col, elem);

    matrix_print(head, rows, cols);

    matrix_destroy(&head);
    matrix_destroy(&A);
    matrix_destroy(&B);
    matrix_destroy(&C);
    matrix_destroy(&D);

    return 0;
    }
    
}
