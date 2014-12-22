#include <stdlib.h>
#include <stdio.h>

#define SIZE 10


int iterativeHighMerge(int *merged , int *a ,int *b ,int N );
int iterativeLowMerge(int *merged , int *a ,int *b ,int N );

int mergeTest();

int main()
{
  printf("Starting Merge Function test ! \n");
  int flag = mergeTest();
  printf("Test %s \n", flag ? "PASSed" : "FAILED" );
  
}

/* Performs a sequence of tests to see if the merge function
 * works as expected using simple iterative merge functions.
*/

int mergeTest()
{
  int *a = (int *)malloc( SIZE * sizeof(int) ) ;
  if ( a == NULL )
  {
    printf("Memory could not be allocated for test array 1 \n");
    return -1;
  }
  
  int *b = (int *)malloc( SIZE * sizeof(int) ) ;

  if ( b == NULL )
  {
    printf("Memory could not be allocated for test array 2 \n");
    return -1;
  }
  int i  ;
  printf("Generating Test Data Set \n");
  for ( i = 0 ; i < SIZE ; i++ )
  {
    a[i] = i;
    b[i] = i + 1 ;
  }
  printf("Finished Generating Test Data Set \n");
  int *merged ;
  // Allocate the memory for the array of merged values
  
  merged = (int *) malloc ( SIZE * sizeof(int) );
  if (merged == NULL )
  {
    printf("Error allocating memory! \n");
    return 0;
  }

// ---------------------------------------------------------
// ---------- Merge Low Tests ------------------------------

  int flag = iterativeLowMerge(merged , a , b , SIZE ) ;
  if ( flag < 0 )
    return 0;
  printf("Finished Iterative Merge Low \n");
  merge( a , b , SIZE , 1 ) ;
  

  int pass = 1 ;
  for ( i = 0 ; i < SIZE ; i++ )
  {
    pass &= ( merged[i] == a[i]  ) ; 
    if ( merged[i] != a[i] )
      printf(" Correct Value = %d Actual Value = %d \n",merged[i] , a[i] );
  }
  
  printf("Merge Low test %s \n", pass ? "PASSed" : "FAILED");

// ---------------------------------------------------------
// ---------- Merge High Tests ----------------------------- 

  printf("Generating Data Set for merge high test \n");

  for ( i = 0 ; i < SIZE ; i++ )
    a[i] = i ;

  flag = iterativeHighMerge(merged , a , b , SIZE );

  if ( flag < 0 ) 
    return 0;

  printf("Finished iterative Merge \n");
  
  merge( a , b , SIZE , -1 ) ;


  return pass;
}

/* Performs an iterative merge of arrays a , b keeping only their
 * highest elements
*/
int iterativeHighMerge(int *merged , int *a ,int *b ,int N )
{
  
  if ( merged == NULL )
  {
    printf("ERROR : Null Pointer detected \n");
    return 0;
  }

  int i = 0 ;
  int j = 0 ;
  int k = 0 ;
  
  // Merge the 2 arrays into one containing the smaller values of the 2 
  // arrays.
  while ( k < N )
  {
   
    if ( a[i] >= b[j] )
    {
      merged[k] = a[i];
      i++;
      k++;
    }
    else
    {
      merged[k] = b[j];
      k++;
      j++;
    }
  }
  // The merge was succesfull.
  return 1;
}


/* Performs an iterative merge of the smallest elements of arrays 
 * a , b
*/
int iterativeLowMerge(int *merged , int *a ,int *b ,int N )
{
  // If the memory for the merged array was not allocated 
  // then allocate it.
  if (merged == NULL )
  {
    merged = (int *) malloc ( N * sizeof(int) ) ;
  }
  if ( merged == NULL )
  {
    printf("Error Allocating memory for array with the correct merge \n");
    return 0;
  }

  int i = 0 ;
  int j = 0 ;
  int k = 0 ;
  
  // Merge the 2 arrays into one containing the smaller values of the 2 
  // arrays.
  while ( k < N )
  {
    if ( a[i] <= b[j] )
    {
      merged[k] = a[i];
      i++;
      k++;
    }
    else
    {
      merged[k] = b[j];
      k++;
      j++;
    }
  }
  return 1;
}





