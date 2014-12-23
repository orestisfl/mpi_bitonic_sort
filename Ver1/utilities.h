#ifndef UTILITIES_H 
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

enum {
      ARG_ERROR = 3,
      MALLOC_ERROR,
      NTHREADS_ERROR
} errors;


// Array size for test purposes.
#define SIZE 100
#define ASCENDING 1
#define DESCENDING -1

/* List of Function Prototypes */

/* Merge Functions */
void* merge_low(int *a, int *b, size_t N);
void* merge_high(int *a, int *b, size_t N);
void merge(int **a, int *b, size_t N, int dir);

/* Compare Function */

void compare(int **local_array, size_t N, int partner, int dir);

/* General Utilities Functions */

int cantor(int a, int b);
void icantor(int z, int res[2]);

/* Prints array a */
void print_array(int *a, int N)
{
      for (int i = 0; i < N; ++i) printf("%d ", a[i]);
      printf("\n");
}

#ifdef MPICH
#include "mpi.h"

/* Print all the arrays of all the processes in ascending
 * process rank order .
*/
void print_all_arrays(int *array, int N, int processID, int numTasks)
{
  int runs = 0;
  while (runs < numTasks) {
    if (processID == runs) {
      printf ("Array printed by rank: %d\n", processID);
      print_array(array, N);
      fflush (stdout);
    }
    runs ++;
    MPI_Barrier (MPI_COMM_WORLD);
  }
}

#endif

/* Function passed to stdlib qsort in order to sort the data in 
 * ascending order. 
*/
int ascending( const void *a , const void *b)
{
    return ( (*(int*)a) - (*(int*)b) );
}


/* Functions used in testing */
int iterativeHighMerge(int *merged , int *a ,int *b ,int N );
int iterativeLowMerge(int *merged , int *a ,int *b ,int N );

int mergeTest();
int comparisonTest( int * trueVal , int *valFound , int N );

/* Function used to test that the given array was successfully 
 * sorted in ascending order.
*/
int ascendingSort(int* array , int N )
{
  int pass = 1;
  int i;
  for (i = 1; i < N; i++) {
    pass &= (a[i-1] <= a[i]);
  }

  printf("Ascending sort TEST %s\n",(pass) ? "PASSed" : "FAILed");

  return pass;
}

#endif 

