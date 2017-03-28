#include <stdio.h>

/* Function used by qsort in order to sort data in ascending order */
int ascendingOrder(const void *a, const void *b) { return ((*(int *)a) - (*(int *)b)); }

/* Function used to print an array */
void print_array(int *a, int N) {
    for (int i = 0; i < N; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/* Function that tests whether the data in the inpu array
 * is sorted in ascending order
*/
int ascendingSort(int *array, int N) {
    int pass = 1;
    int i;
    for (i = 1; i < N; i++) {
        pass &= (array[i - 1] <= array[i]);
    }

    printf("Ascending sort TEST %s\n", (pass) ? "PASSed" : "FAILed");

    return pass;
}
