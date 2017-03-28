#ifndef UTILITIES_H
#define UTILITIES_H
#include <stdlib.h>

enum { ARG_ERROR = 3, MALLOC_ERROR, NTHREADS_ERROR } errors;

// Array size for test purposes.
#define SIZE 100
#define ASCENDING 1
#define HIGH 1
#define DESCENDING -1
#define LOW -1
#define MASTER 0

void merge(int **a, int *b, size_t N, int dir);
void merge_2N(int *a, int *b, size_t N, int dir);

void compare(int **local_array, size_t N, int partner, int dir);
int cantor(int a, int b);
void icantor(int z, int res[2]);
void print_array(int *a, int N);
void print_all_arrays(int *array, int N, int processID, int numTasks);

int ascendingOrder(const void *a, const void *b);

int iterativeHighMerge(int *merged, int *a, int *b, int N);
int iterativeLowMerge(int *merged, int *a, int *b, int N);
int mergeTest();
int comparisonTest(int *trueVal, int *valFound, int N);
int ascendingSort(int *array, int N);
#endif
