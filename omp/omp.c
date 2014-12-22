#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

struct timeval startwtime, endwtime;
double seq_time;


int N;          // data array size
int *a;         // data array to be sorted

const int ASCENDING  = 1;
const int DESCENDING = 0;


void init(void);
void print(void);
void sort(void);
void test(void);
inline void exchange(int i, int j);
void compare(int i, int j, int dir);
void bitonicMerge(int lo, int cnt, int dir);
void recBitonicSort(int lo, int cnt, int dir);
void impBitonicSort(void);
void parallelImpBitonicSort(void);

/** the main program **/
int main(int argc, char **argv)
{

    if (argc != 2) {
        printf("Usage: %s q\n  where n=2^q is problem size (power of two)\n",
               argv[0]);
        exit(1);
    }

    N = 1 << atoi(argv[1]);
    a = (int *) malloc(N * sizeof(int));

    init();

    gettimeofday (&startwtime, NULL);
    impBitonicSort();
    gettimeofday (&endwtime, NULL);

    seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec) / 1.0e6
                        + endwtime.tv_sec - startwtime.tv_sec);

    printf("\nImperative wall clock time = %f\n", seq_time);

    test();
    // Parallel Imperative Bitonic Sort.
    init();

    gettimeofday (&startwtime, NULL);
    parallelImpBitonicSort();
    gettimeofday (&endwtime, NULL);

    seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec) / 1.0e6
                        + endwtime.tv_sec - startwtime.tv_sec);

    printf("\nParallel Imperative wall clock time = %f\n", seq_time);

    test();


    init();
    gettimeofday (&startwtime, NULL);
    sort();
    gettimeofday (&endwtime, NULL);

    seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec) / 1.0e6
                        + endwtime.tv_sec - startwtime.tv_sec);

    printf("Recursive wall clock time = %f\n", seq_time);

    test();

    // print();
}

/** -------------- SUB-PROCEDURES  ----------------- **/

/** procedure test() : verify sort results **/
void test()
{
    int pass = 1;
    int i;
    //~ printf("%d ", a[0]);
    for (i = 1; i < N; i++) {
        //~ printf("%d ", a[i]);
        pass &= (a[i - 1] <= a[i]);
    }
    //~ printf("\n");

    printf(" TEST %s\n", (pass) ? "PASSed" : "FAILed");
}


/** procedure init() : initialize array "a" with data **/
void init()
{
    int i;
    for (i = 0; i < N; i++) {
        a[i] = rand() % N; // (N - i);
        //~ printf("%d ", a[i]);
    }
    //~ printf("\n");
}

/** procedure  print() : print array elements **/
void print()
{
    int i;
    for (i = 0; i < N; i++) {
        printf("%d\n", a[i]);
    }
    printf("\n");
}


/** INLINE procedure exchange() : pair swap **/
inline void exchange(int i, int j)
{
    int t;
    t = a[i];
    a[i] = a[j];
    a[j] = t;
}



/** procedure compare()
   The parameter dir indicates the sorting direction, ASCENDING
   or DESCENDING; if (a[i] > a[j]) agrees with the direction,
   then a[i] and a[j] are interchanged.
**/
inline void compare(int i, int j, int dir)
{
    if (dir == (a[i] > a[j]))
        exchange(i, j);
}




/** Procedure bitonicMerge()
   It recursively sorts a bitonic sequence in ascending order,
   if dir = ASCENDING, and in descending order otherwise.
   The sequence to be sorted starts at index position lo,
   the parameter cbt is the number of elements to be sorted.
 **/
void bitonicMerge(int lo, int cnt, int dir)
{
    if (cnt > 1) {
        int k = cnt / 2;
        int i;
        for (i = lo; i < lo + k; i++)
            compare(i, i + k, dir);
        bitonicMerge(lo, k, dir);
        bitonicMerge(lo + k, k, dir);
    }
}



/** function recBitonicSort()
    first produces a bitonic sequence by recursively sorting
    its two halves in opposite sorting orders, and then
    calls bitonicMerge to make them in the same order
 **/
void recBitonicSort(int lo, int cnt, int dir)
{
    if (cnt > 1) {
        int k = cnt / 2;
        recBitonicSort(lo, k, ASCENDING);
        recBitonicSort(lo + k, k, DESCENDING);
        bitonicMerge(lo, cnt, dir);
    }
}


/** function sort()
   Caller of recBitonicSort for sorting the entire array of length N
   in ASCENDING order
 **/
void sort()
{
    recBitonicSort(0, N, ASCENDING);
}


/*
 * Imperative Version of Bitonic Sort.
 */

void impBitonicSort()
{

    int i, j, k;
    int ij;

    for (k = 2; k <= N; k = 2 * k) {
        for (j = k >> 1; j > 0; j = j >> 1) {       
            for (i = 0; i < N; i++) {
                ij = i ^ j;
                if (ij > i) {
                    if ((i & k) == 0 && a[i] > a[ij])
                        exchange(i, ij);
                    if ((i & k) != 0 && a[i] < a[ij])
                        exchange(i, ij);
                }

            }
        }
    }
}

/*
  Parallel imperative version of bitonic sort
*/
void parallelImpBitonicSort()
{

    int i, j, k;
    int ij;

    for (k = 2; k <= N; k = 2 * k) {
        for (j = k >> 1; j > 0; j = j >> 1) {
            #pragma omp parallel for private(ij)
            for (i = 0; i < N; i++) {
                ij = i ^ j;
                if (ij > i) {
                    if ((i & k) == 0 && a[i] > a[ij])
                        exchange(i, ij);
                    if ((i & k) != 0 && a[i] < a[ij])
                        exchange(i, ij);
                }

            }
        }
    }
}
