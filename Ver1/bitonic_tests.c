#include <stdlib.h>
#include <stdio.h>

#define SIZE 10


int iterativeHighMerge(int *merged , int *a ,int *b ,int N );
int iterativeLowMerge(int *merged , int *a ,int *b ,int N );
void merge(int *a, int *b, size_t N);
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


  int flag = iterativeLowMerge(merged , a , b , SIZE ) ;
  if ( flag < 0 )
    return 0;
  printf("Finished Iterative Merge \n");
  merge( a , b , SIZE ) ;
  
  int pass = 1 ;
  for ( i = 0 ; i < SIZE ; i++ )
  {
    pass &= ( merged[i] == a[i]  ) ; 
    if ( merged[i] != a[i] )
      printf(" Correct Value = %d Actual Value = %d \n",merged[i] , a[i] );
  }
  

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


/* Function used to test if a sequence contained in array
 * a was successfully sorted.
*/
int sortingTest(int *a ,int N)
{
  int pass = 1;
  int i;
  for (i = 1; i < N ; i++) {
    pass &= (a[i - 1] <= a[i] ) ;
  }

  printf("sorted TEST %s\n", (pass) ? "PASSed" : "FAILED" );
  return pass ;
}

void merge(int *a, int *b, size_t N)
{
  /* a: result array
   * b: 2nd array for the merging
   * i: index of array a
   * j: index of array b */
  int j = 0;
  int beh = 0;
  int cases[8] = {0};

  for(int i = 0; i < N; ++i) {
    if (beh < 0) printf("WARNING beh<0\n");
    if (beh) {
      /* the smaller elements of are on the behind */
      if (b[j] <= a[N - 1]) {
        cases[0] = 1;
        /* b[j] is still smaller than beh elements */
        if(N - beh > i) {
          cases[1] = 1;
          beh++;
          a[N - beh] = a[i];
        } else {
          cases[2] = 1;
          /* start replacing beh elements
           * because we've reached the back_fits (i) */
          beh--;
        }
        a[i] = b[j++];
      } else {
        cases[3] = 1;
        /* beh element smaller than b[j]. put it in a[i]*/
        int repl = a[N - 1];
        int back_fits = N - beh > i;

        if(back_fits) a[N - beh] = a[i];
        if(back_fits) cases[4] = 1;

        /* and swift the rest elements. */
        memmove(&a[N - beh + 1], &a[N - beh], (beh - 1) * sizeof(int));
        a[i] = repl;
        if (!back_fits) beh--;
        if (!back_fits) cases[5] = 1;
      }

    } else {
      if (b[j] < a[i]) {
        cases[6] = 1;
        if(N - beh > i) {
          cases[7] = 1;
          beh++;
          a[N - beh] = a[i];
        } else {
          cases[8] = 1;
          /* start replacing beh elements
           * because we've reached the back_fits (i) */
          beh--;
        }
        a[i] = b[j++];
      }
    }
  }
}
    
