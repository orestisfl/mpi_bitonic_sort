#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED
#define MASTER 0

enum {
    ARG_ERROR = 3,
    MALLOC_ERROR,
    NTHREADS_ERROR
} errors;


// Function that is used by each process to communicate with
// the corresponding process by the calling one and perform
// void mergeHigh(int *localArray,int N, );
// void mergeLow();


/* Function passed to the std lib quicksort in order to sort
 * an array in ascending order. 
*/

int Ascending(const void *a, const void *b)
{
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a == *(int*)b ) return 0;
  if ( *(int*)a >  *(int*)b ) return 1;
}

/* Function passed to the std lib quicksort in order to sort
 * an array in Descending order. 
*/

int Descending(const void *a, const void *b)
{
  if ( *(int*)a <  *(int*)b ) return 1;
  if ( *(int*)a == *(int*)b ) return 0;
  if ( *(int*)a >  *(int*)b ) return -1;
  
}

int main(int argc , char** argv)
{
    // ID of the process.
    int processID;

    int *array;
    // The number of elements in the local data array.
    int N;
    int numTasks;

    int i, j ;

    int p , q ;

    // Check if enough arguments were passed to each process.
    if ( argc < 3) {
        // If not print a warning message with the correct way to use
        // the program and terminate the execution.
        printf("Invalid command line argument option! \n");
        printf("Usage : %s p q where p is the number of MPI processes to "
               "be spawned and q the number of elements in each process. \n ",
               argv[0] );
        exit(ARG_ERROR);
    }

    // Initialize the MPI processes and pass the command line
    // arguments to every one of them.

    MPI_Init( &argc , &argv);

    // Get the number of tasks running
    MPI_Comm_size( MPI_COMM_WORLD , &numTasks);

    // Get the id of the process from the MPI daemon.
    MPI_Comm_rank( MPI_COMM_WORLD , &processID);

    // Parse the command line arguments.
    p = atoi( argv[1]);
    q = atoi( argv[2]);



    // The master process checks that the correct number of processes
    // has started working.

    if (processID == 0 && numTasks != ( 1 << p) ) {
        printf("The number of tasks is not equal to the one passed to "
               "the master process and thus the sorting procedure will stop! \n");

        // Terminate the MPI processes.
        MPI_Abort(MPI_COMM_WORLD, NTHREADS_ERROR);
        exit(NTHREADS_ERROR);
    }

    /*Calculate the total number of elements.
     * and create the dataset */
    N = 1 << q ;

    printf("Process %d has started generating the dataset! \n", processID);
    array = (int *)malloc( N * sizeof(int) );

    if ( array == NULL ) {
        printf("Process %d failed to allocate the memory required for the"
               " data array \n", processID);
        MPI_Abort(MPI_COMM_WORLD, MALLOC_ERROR);
        exit(MALLOC_ERROR);
    }

    srand(time(NULL) * (processID + 1));
    for ( i = 0 ; i < N ; i++ ) {
        array[i] = rand() % N  ;
    }
    
    // Sort all the elements in ascending order.
    qsort( array , N , int , Ascending );
    
    // Wait for all the tasks to generate the data set.
    MPI_Barrier(MPI_COMM_WORLD);


    // Wait for all processes to finish sorting. (MPI_BARRIER)


    // If the test macro is enabled print that the sorting finished
    // successfully and perform verification tests.
#ifdef TEST
    if (processID == 0 ) {
        printf("The sorting procedure finished! \n");

        // Call the test routines to see if the procedure was successful.
    }

#endif

    free(array);
    MPI_Finalize();
    return 0;

}
