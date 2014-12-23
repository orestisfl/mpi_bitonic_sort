#include "merge.h"


/* Function that is called by a process in order to exchange data
 * keeps either smaller or larger elements of the 2 arrays */
void compare(int **local_array, size_t N, int partner, int dir)
{
    int rank;
    MPI_Request reqs[2];
    MPI_Status stats[2];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int cantor_arg1 = (dir == ASCENDING)? rank : partner;
    int cantor_arg2 = (dir == ASCENDING)? partner : rank;
    int send_tag = (1 + (dir == ASCENDING ))  * cantor(cantor_arg1, cantor_arg2);
    int recv_tag = (1 + (dir == DESCENDING )) * cantor(cantor_arg1, cantor_arg2);

    printf("rank=%d partner=%d send_tag=%d recv_tag=%d\n", rank, partner, send_tag, recv_tag);

    int *received_array = malloc(N * sizeof(int));
    if (dir == ASCENDING ) {
        /* first send then receive */
        MPI_Isend(*local_array  , N, MPI_INT, partner, send_tag, MPI_COMM_WORLD,
                  &reqs[0]);
        MPI_Irecv(received_array, N, MPI_INT, partner, recv_tag, MPI_COMM_WORLD,
                  &reqs[1]);
    } else {
        /* first receive then send */
        MPI_Irecv(received_array, N, MPI_INT, partner, recv_tag, MPI_COMM_WORLD,
                  &reqs[1]);
        MPI_Isend(*local_array  , N, MPI_INT, partner, send_tag, MPI_COMM_WORLD,
                  &reqs[0]);
    }

    /* we shouldn't modify the local_array
     * until our partner receives it, so we wait */
    MPI_Waitall(2, reqs, stats);

    /* merge the local and the received array.
     * Result on local_array pointer. */
    merge(local_array, received_array, N, dir);
    free(received_array);
}
