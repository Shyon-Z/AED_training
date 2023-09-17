#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int nums[1000];
    int numsize[10] = {0};
    int k;
    char sel;
    int check[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("Enter numbers to be added to the array.\n");

    int i = 0;

    while (1) {
        scanf("%d", &nums[i]);
        i++;

        printf("To add another number, enter 's'; otherwise, enter 'n': ");
        scanf(" %c", &sel);

        if (sel != 's' && sel != 'S') {
            break;
        }
    }

    int numElements = i;

    printf("Enter the value of k: ");
    scanf("%d", &k);

    for (i = 0; i < numElements; i++) {
        for (int j = 0; j < 10; j++) {
            if (nums[i] == check[j]) {
                numsize[j]++;
                break;
            }
        }
    }

    printf("The top %d most frequent elements are:\n", k);

    for (i = 0; i < k; i++) {
        int index = 0;

        for (int j = 0; j < 10; j++) {
            if (numsize[j] > numsize[index]) {
                index = j;
            }
        }

        if (numsize[index] == 0) {
            break; 
        }

        printf("%d (Frequency: %d)\n", check[index], numsize[index]);
        numsize[index] = 0;
    }

    return 0;
}


/*
make a user inputed array (in case i can't make it, use a rand)

make the 0-9 array to check (check the K for the limit of frequency)
    use strcmp to check a character/number and put a counter of the character into numsize
        loop till the end of vector

put the counters on returnsize
*/