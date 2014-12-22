#include <stdlib.h>
#include <string.h>

/* Function that merges arrays a , b into one by keeping only their N
 * smallest values
*/
void mergeLow(int *a, int *b, size_t N)
{
    /* a: result array
     * b: 2nd array for the merging
     * i: index of array a
     * j: index of array b */
    int j = 0;
    int behind = 0;

    for(int i = 0; i < N; ++i) {
        if (behind) {
            /* the smaller elements of are on the behind */
            if (b[j] <= a[N - 1]) {
                /* b[j] is still smaller than behind elements */
                if(N - behind > i) {
                    behind++;
                    a[N - behind] = a[i];
                } else {
                    /* start replacing behind elements
                     * because we've reached the back_fits (i) */
                    behind--;
                }
                a[i] = b[j++];
            } else {
                /* behind element smaller than b[j]. put it in a[i]*/
                int repl = a[N - 1];
                int back_fits = N - behind > i;

                /* and switch the rest of the elements. */
                memmove(&a[N - behind + 1], &a[N - behind] ,
                    (behind - 1) * sizeof(int));

                if(back_fits) a[N - behind] = a[i];
                  a[i] = repl;
                if (!back_fits) 
                  behind--;
            }

        } else {
            if (b[j] < a[i]) {
                if(N - behind > i) {
                    behind++;
                    a[N - behind] = a[i];
                } else {
                    /* start replacing behind elements
                     * because we've reached the back_fits (i) */
                    behind--;
                }
                a[i] = b[j++];
            }
        }
    }

}
