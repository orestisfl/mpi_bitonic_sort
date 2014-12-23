#include <stdlib.h>
#include <stdio.h>

void merge(int *a, int *b, size_t N, int dir)
{
  /* a: result array
   *      * b: 2nd array for the merging
   *           * i: index of array a
   *                * j: index of array b */

  int beh = 0;
  int cases[8] = {0};

  int ascending = dir == 1;
  int start = (ascending) ? 0 : N - 1;
  int end = (ascending) ? N : -1;
  int behind_start = (ascending) ? end - 1 : 0;

  int j = start;

  for(int i = start; i != end; i += dir) {
    if (beh < 0) printf("WARNING beh<0\n");
    if (beh) {
      /* the smaller elements of are on the behind */
      if (b[j] * dir <= a[behind_start] * dir) {
        cases[0] = 1;
        /* b[j] is still smaller than beh elements */
        if((end - beh * dir - i)*dir > 0) {
          cases[1] = 1;
          beh++;
          a[end - beh * dir] = a[i];
        } else {
          cases[2] = 1;
          /* start replacing beh elements
           *                      * because we've reached the back_fits (i) */
          beh--;
        }
        a[i] = b[j];
        j += dir;
      } else {
        cases[3] = 1;
        
        /* beh element smaller than b[j]. put it in a[i]*/
        int repl = a[behind_start];
        int back_fits = (end - beh * dir - i) * dir > 0;

        /* and swift the rest elements. */
        //~ printf("dest=%d src=%d beh-1=%d\na pou memmove (src,dest)= ", end - beh*dir + 1, end - beh*dir, beh-1);
        //~ print_array(&a[end - beh*dir], beh-1);
        //~ print_array(&a[end - beh * dir + dir], beh-1);

        int src =  ascending? end - beh : behind_start+1;
        int dest = ascending? end - beh + 1 : behind_start;
        memmove(&a[dest], &a[src], (beh - 1) * sizeof(int));

        if(back_fits) a[end - beh * dir] = a[i];
        a[i] = repl;
        if (!back_fits) beh--;
        if(back_fits) cases[4] = 1;
        if (!back_fits) cases[5] = 1;

        //~ printf("i=%d: repl=%d back_fits=%d a[i]=%d\n\n", i, repl, back_fits, a[i]);

      }

    } else {
      if (b[j] * dir < a[i] * dir) {
        cases[6] = 1;
        if((end - beh * dir - i)*dir > 0) {
          cases[7] = 1;
          beh++;
          a[end - beh * dir] = a[i];
        } else {
          cases[8] = 1;
          /* start replacing beh elements
           * because we've reached the back_fits (i) */
          beh--;
        }
        a[i] = b[j];
        j += dir;
      }
      /*else keep a[i]*/
    }
    //~ printf("i=%d:\n", i);
    //~ print_array(a, SIZE);

  }

  for (int l = 0; l < 8; ++l) {
    if (!cases[l]) printf("!cases: %d\n", l);
  }

}

