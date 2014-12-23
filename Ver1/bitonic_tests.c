#include "utilities.h"

int main()
{
  printf("Starting Merge Function test ! \n");
  int flag = mergeTest();
  printf("Test %s \n", flag ? "PASSed" : "FAILED" );
  
}

/* Performs a sequence of tests to see if the merge function
 * works as expected using simple iterative merge functions.
*/


int comparisonTest( int * trueVal , int *valFound , int N )
{
  int i ;
  int pass = 1 ;
  for ( i = 0 ; i < N ; i++ )
  {
    pass &= ( trueVal[i] == valFound[i]  ) ; 
    if ( trueVal[i] != valFound[i] )
      printf(" Correct Value = %d Actual Value = %d \n",trueVal[i] ,
          valFound[i] );
  }
  return pass;
}


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
  
  int pass = comparisonTest( merged , a , SIZE );
 
  printf("Merge Low test %s \n", pass ? "PASSed" : "FAILED");

// ---------------------------------------------------------
// ---------- Merge High Tests ----------------------------- 
  
  // b[i] - a[i] = 1 .
  printf("Generating Data Set for merge high test \n");

  for ( i = 0 ; i < SIZE ; i++ )
    a[i] = i ;

  flag = iterativeHighMerge(merged , a , b , SIZE );

  if ( flag < 0 ) 
    return 0;

  printf("Finished iterative Merge \n");
  
  merge( a , b , SIZE , -1 ) ;
 
  pass = comparisonTest( merged , a , SIZE ); 
  printf("Merge High test 1 %s \n", pass ? "PASSed" : "FAILED");
  
  // b[i] - a[i] = SIZE .

  for ( i = 0 ; i < SIZE ; i++ )
  {
    a[i] = i ;
    b[i] = i + SIZE;
  }
  flag = iterativeHighMerge(merged , a , b , SIZE );

  if ( flag < 0 ) 
    return 0;

  printf("Finished iterative Merge \n");
  
  merge( a , b , SIZE , -1 ) ;
 
  pass = comparisonTest( merged , a , SIZE ); 
  printf("Merge High test 2 %s \n", pass ? "PASSed" : "FAILED");
  

  // Random Numbers Arrays.

  srand(time(NULL));
  for ( i = 0 ; i < SIZE ; i++ )
  {
    a[i] = rand() % SIZE ;
    b[i] = rand() % SIZE ;
  }

  // Sort them for the merge to work.
  qsort( a , SIZE , sizeof(int) , ascending );
  qsort( b , SIZE , sizeof(int) , ascending );

  // Call the function that performs the correct merge.
  flag = iterativeHighMerge(merged , a , b , SIZE );

  if ( flag < 0 ) 
    return 0;

  printf("Finished iterative Merge \n");
  
  // Perform our merge.
  merge( a , b , SIZE , -1 ) ;
 
  pass = comparisonTest( merged , a , SIZE ); 
  printf("Merge High Random Number test %s \n", pass ? "PASSed" : "FAILED");
  
  free(a);
  free(b);
  free(merged);
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

  int i = N - 1 ;
  int j = N - 1 ;
  int k = N - 1 ;
  
  // Merge the 2 arrays into one containing the smaller values of the 2 
  // arrays.
  while ( k >= 0  )
  {
   
    if ( a[i] >= b[j] )
    {
      merged[k] = a[i];
      i--;
      k--;
    }
    else
    {
      merged[k] = b[j];
      k--;
      j--;
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





