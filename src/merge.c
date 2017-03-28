#include "utilities.h"
#include <stdlib.h>
#include <string.h>

/* keeps the smaller elements of the 2 arrays.
 * returns result pointer of the sorted array */
void *merge_low(int *a, int *b, size_t N) {
    int k = 0;
    int j = 0;

    int *result = malloc(N * sizeof(int));

    /* merging the two sorted arrays
    * we have 2N elements and we need N,
    * so there is no way to have leftovers*/
    for (size_t i = 0; i < N; ++i) {
        if (a[j] < b[k]) {
            result[i] = a[j++];
        } else {
            result[i] = b[k++];
        }
    }

    return result;
}

/* keeps the larger elements of the 2 arrays.
 * returns result pointer of the sorted array */
void *merge_high(int *a, int *b, size_t N) {
    int k = N - 1;
    int j = N - 1;

    int *result = malloc(N * sizeof(int));

    for (int i = N - 1; i >= 0; --i) {
        if (a[j] > b[k]) {
            result[i] = a[j--];
        } else {
            result[i] = b[k--];
        }
    }

    return result;
}

/* Main merge function that calls either merge low or merge high
 * depending on the value of the direction argument.
*/
void merge(int **a, int *b, size_t N, int dir) {
    /* result of the requested merge.  */
    int *res = (dir == ASCENDING) ? merge_low(*a, b, N) : merge_high(*a, b, N);
    free(*a);
    *a = res;
}

/* Function that merges 2 arrays into one without using an extra
 * memory buffer.
*/
void merge_2N(int *a, int *b, size_t N, int dir) {
    /* merge that only used O(1) (extra) space. Current implementation extremely slow. */
    /* a: result array
     * b: 2nd array for the merging
     * i: index of array a
     * j: index of array b */

    int behind = 0;

    int ascending = dir == 1;
    int start = (ascending) ? 0 : N - 1;
    int end = (ascending) ? (int)N : -1;
    int behind_start = (ascending) ? end - 1 : 0;

    int j = start;

    for (int i = start; i != end; i += dir) {
        if (behind) {
            /* the smaller elements of are on the behind */
            if (b[j] * dir <= a[behind_start] * dir) {
                /* b[j] is still smaller than behind elements */
                if ((end - behind * dir - i) * dir > 0) {
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
                int src = ascending ? end - behind : 1;
                int dest = ascending ? end - behind + 1 : 0;
                memmove(&a[dest], &a[src], (behind - 1) * sizeof(int));

                if (back_fits) {
                    a[end - behind * dir] = a[i];
                }
                a[i] = tmp;
                if (!back_fits) {
                    behind--;
                }
            }

        } else {
            if (b[j] * dir < a[i] * dir) {
                if ((end - behind * dir - i) * dir > 0) {
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
