#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 
#define MASTER 0


// Function that is used by each process to communicate with
// the corresponding process by the calling one and perform
// void mergeHigh(int *localArray,int N, );
// void mergeLow();

int main(int argc , char** argv)
{
  // ID of the process.
  int processID;

  int *array;
  // The number of elements in the local data array.
  int N;
  
  int numTasks;
  
  // Loop indices.
  int i , j ;

  int p , q ;

  // Check if enough arguments were passed to each process.
  if ( argc < 3)
  {
    // If not print a warning message with the correct way to use
    // the program and terminate the execution.
    printf("Invalid command line argument option! \n");
    printf("Usage : %s p q where p is the number of MPI processes to "
    "be spawned and q the number of elements in each process. \n ", 
    argv[0] );
    MPI_Finalize();
    return -1;
  }

   // Initialize the MPI processes and pass the command line 
  // arguments to every one of them.

  MPI_INIT( &argc , &argv);

  // Get the number of tasks running
  MPI_Comm_size( MPI_COMM_WORLD , &numTasks);
  
  // Get the id of the process from the MPI daemon.
  MPI_Comm_rank( MPI_COMM_WORLD , &processID); 
  
  // Parse the command line arguments.
  p = atoi( argv[1]);
  q = atoi( argv[2]);
  


  // The master process checks that the correct number of processes
  // has started working.

  if (  numTasks != ( 1 << p) )
  {
    printf("The number of tasks is not equal to the one passed to "
    "the master process and thus the sorting procedure will stop! \n");
    
    // Terminate the MPI processes.
   MPI_Finalize(); 
    
    // Finish the execution.
    return -1;
  }
  
  
  

  
  // Calculate the total number of elements.
  N = 1 << q ;   

// ------------------------------------------------------------------------- 
// ------------------------------------------------------------------------- 
// ------------------------------------------------------------------------- 

  // Create the data set using a random number generator.
  
  // Allocate the necessary memory.
  array = (int *)malloc( N * sizeof(int) );
  
  if ( array == NULL )
  {
    printf("Process %d failed to allocate the memory required for the"
    " data array \n",processID);
    MPI_ABORT(MPI_COMM_WORLD);
    return -1;
  }
  
  printf("Process %d has started generating the dataset! \n",processID);

  srand(time(NULL));  
  for ( i = 0 ; i < N ; i++ )
  {
    array[i] = rand() % N  ;
  }

  // Wait for all the tasks to generate the data set.
 
  MPI_Barrier(MPI_COMM_WORLD);      
  
   
  // Wait for all processes to finish sorting. (MPI_BARRIER)
  
  
  // If the test macro is enabled print that the sorting finished 
  // successfully and perform verification tests.
  #ifdef TEST
  if (processID == 0 )
  {
    printf("The sorting procedure finished! \n");
    
    // Call the test routines to see if the procedure was successful.
  }
  
  #endif
  
  free(array);  
  // Terminate the MPI environment.
  MPI_Finalize();


  return 0;
  
}
