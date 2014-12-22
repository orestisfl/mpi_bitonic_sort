#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>




int cantor(int a, int b)
{
    /*pairing function
     *https://en.wikipedia.org/wiki/Pairing_function
     *https://math.stackexchange.com/questions/23503/create-unique-number-from-2-numbers
     * */
    return (a + b) * (a + b + 1) / 2 + b;
}

void icantor(int z, int res[2])
{
    int w = (int)((sqrt(8 * z - 1)) / 2);
    int t = (w * w + w) / 2;
    res[0] = z - t;
    res[1] = w - res[0];
}



void CompareLow(int *local_array, size_t N, int partner)
{

    /* allocate space for new array, receive and send data*/
    int *received_array = malloc(N * sizeof(int));

    int rank;
    MPI_Request reqs[2];
    MPI_Status stats[2];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int send_tag = 2 * cantor(rank, partner);
    int recv_tag = cantor(rank, partner);

    MPI_Isend(local_array   , N, MPI_INT, partner, send_tag, MPI_COMM_WORLD, &reqs[0]);
    MPI_Irecv(received_array, N, MPI_INT, partner, recv_tag, MPI_COMM_WORLD, &reqs[0]);

    /* we shouldn't modify the local_array
     * until our partner receives it, so we wait */
    MPI_Waitall(2, reqs, stats);

    /* merging the two sorted arrays
     * we have 2N elements and we need N,
     * so there is no way to have leftovers*/
    merge(local_array, received_array, N);
}

void CompareHigh(int *local_array, size_t N, int partner);
