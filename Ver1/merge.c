#include <stdlib.h>
#include <string.h>

void merge(int *a, int *b, size_t N, int dir)
{
    /* a: result array
     * b: 2nd array for the merging
     * i: index of array a
     * j: index of array b */

    int behind = 0;

    int ascending = dir == 1;
    int start = (ascending) ? 0 : N - 1;
    int end = (ascending) ? N : -1;
    int behind_start = (ascending) ? end - 1 : 0;

    int j = start;

    for(int i = start; i != end; i += dir) {
        if (behind) {
            /* the smaller elements of are on the behind */
            if (b[j] * dir <= a[behind_start] * dir) {
                /* b[j] is still smaller than behind elements */
                if((end - behind * dir - i)*dir > 0) {
                    behind++;
                    a[end - behind * dir] = a[i];
                } else {
                    /* start replacing behind elements
                     * because we've reached the back_fits (i) */
                    behind--;
                }
                a[i] = b[j];
                j += dir;
            } else {
                /* behind element smaller than b[j]. put it in a[i]*/
                int tmp = a[behind_start];
                int back_fits = (end - behind * dir - i) * dir > 0;

                /* and swift the rest elements. */
                /* ascending => right shift else left shift */
                int src =  ascending ? end - behind : 1;
                int dest = ascending ? end - behind + 1 : 0;
                memmove(&a[dest], &a[src], (behind - 1) * sizeof(int));

                if(back_fits) a[end - behind * dir] = a[i];
                a[i] = tmp;
                if (!back_fits) behind--;
            }

        } else {
            if (b[j] * dir < a[i] * dir) {
                if((end - behind * dir - i)*dir > 0) {
                    behind++;
                    a[end - behind * dir] = a[i];
                } else {
                    /* start replacing behind elements
                     * because we've reached the back_fits (i) */
                    behind--;
                }
                a[i] = b[j];
                j += dir;
            }
            /*else keep a[i]*/
        }
    }
}
