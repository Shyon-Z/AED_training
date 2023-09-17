#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double program_timer(void (*sort_function)(int[], int, int), int subject[], int low, int high) {
    clock_t start, end;

    start = clock();

    sort_function(subject, low, high);

    end = clock();

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    return cpu_time_used;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int insertionSort(int subject[], int n) {
   
    int i, key, j;

    for (i = 1; i < n; i++) {
        key = subject[i];
        j = i - 1;

        while (j >= 0 && subject[j] > key) {
            subject[j + 1] = subject[j];
            j = j - 1;
        }
        subject[j + 1] = key;
    }
    return 0;
}

void insertion_failsafe(int subject[], int low, int high) {
    insertionSort(subject, high - low + 1);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int partition(int subject[], int low, int high) {
    int pivot = subject[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (subject[j] <= pivot) {
            i++; 
            int temp = subject[i];
            subject[i] = subject[j];
            subject[j] = temp;
        }
    }

    int temp = subject[i + 1];
    subject[i + 1] = subject[high];
    subject[high] = temp;
    return (i + 1);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

int quicksort(int subject[], int low, int high) {
    if (low < high) {
        int pi = partition(subject, low, high);
        quicksort(subject, low, pi - 1);
        quicksort(subject, pi + 1, high);
    }
    
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void merge(int subject[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            subject[k++] = left[i++];
        } else {
            subject[k++] = right[j++];
        }
    }

    while (i < leftSize) {
        subject[k++] = left[i++];
    }

    while (j < rightSize) {
        subject[k++] = right[j++];
    }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

void mergeSort(int subject[], int n) {
    if (n <= 1) {
        return;
    }

    int mid = n / 2;
    int* left = (int*)malloc(mid * sizeof(int));
    int* right = (int*)malloc((n - mid) * sizeof(int));

    if (left == NULL || right == NULL) {
        printf("error\n");
        exit(1);
    }

    for (int i = 0; i < mid; i++) {
        left[i] = subject[i];
    }
    for (int i = mid; i < n; i++) {
        right[i - mid] = subject[i];
    }

    mergeSort(left, mid);
    mergeSort(right, n - mid);

    merge(subject, left, mid, right, n - mid);

    free(left);
    free(right);
}


void merge_failsafe(int subject[], int low, int high) {
    mergeSort(subject + low, high - low + 1);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int n, sel;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *subject = (int *)malloc(n * sizeof(int));

    if (subject == NULL) {
        printf("error.\n");
        return 1;
    }

    srand(time(NULL));

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        subject[i] = rand() % n;
        printf("%d ", subject[i]);
    }
    printf("\n");

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

    printf("Select the type of sorting you would like to test:\n");
    printf("1. Insertion Sort\n");
    printf("2. Quick Sort\n");
    printf("3. Merge Sort\n");
    scanf("%d", &sel);

    if (sel < 1 || sel > 3) {
        printf("Invalid choice.\n");
        free(subject);
        return 1;
    }

    double timer;
    char *sort_type;

switch (sel) {
    case 1:
        sort_type = "Insertion Sort";
        timer = program_timer(insertion_failsafe, subject, 0, n - 1);
        break;
    case 2:
        sort_type = "Quick Sort";
        timer = program_timer(quicksort, subject, 0, n - 1);
        break;
    case 3:
        sort_type = "Merge Sort";
        timer = program_timer(merge_failsafe, subject, 0, n - 1);
        break;
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", subject[i]);
    }
    printf("\n");
    printf("\n");

    printf("%s took %.3f seconds to complete.\n", sort_type, timer);

    printf("\n");
    printf("\n");

    free(subject);

    
    while (1) {

    printf("\n Press 'q' to quit, any other key to continue...\n");
    char salvation = getchar();
    if (salvation == 'q') {
        break; 
    }
    }

    return 0;
}
