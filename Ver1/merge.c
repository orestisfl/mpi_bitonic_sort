#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//~ #include <math.h>
//~ #include <time.h>

#define SIZE 2000000
void print_array(int *a, int N)
{
    for (int i = 0; i < N; ++i) printf("%d ", a[i]);
    printf("\n");
}

int test(int *a)
{
    int pass = 1;
    int i;
    for (i = 1; i < SIZE; i++) {
        pass &= (a[i - 1] <= a[i]);
    }

    printf("sorted TEST %s\n", (pass) ? "PASSed" : "FAILed");
    return pass;
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
        //~ printf("i=%d:\n", i);
        //~ if (test(a)) printf(" ACK: ");
        //~ else printf("NACK: ");
        //~ print_array(a, SIZE);
        
    }

for (int l = 0; l < 8; ++l) {
        if (!cases[l]) printf("!cases: %d\n", l);
    }

}

void init(int *a, int *b)
{
    int i;
    for (i = 0; i < SIZE; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }
}


int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - * (int*)b );
}


int main()
{
    int a[SIZE], b[SIZE];
    init(a, b);
    qsort(a, SIZE, sizeof(int), cmpfunc);
    printf("a:\n");
    //~ print_array(a, SIZE);
    qsort(b, SIZE, sizeof(int), cmpfunc);
    printf("b:\n");
    //~ print_array(b, SIZE);

    merge(a, b, SIZE);
    test(a);
    //~ print_array(a, SIZE);
    return 0;
}
