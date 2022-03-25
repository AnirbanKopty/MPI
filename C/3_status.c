#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, num;
    MPI_Status status;

    // MPI_Initialization
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // code here
    if(rank==3)
    {
        num =30;
        MPI_Send(&num, 1, MPI_INT, 1, 101, MPI_COMM_WORLD);  // Thus the element size doesn't mean character length, rather number of elements out of an array
        printf("Sender side Rank %d: Num=%d \n", rank, num);
    }

    if(rank==1)
    {
        // use of wildcards at receiver side
        MPI_Recv(&num, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("Receiver side Rank %d : Num=%d, Source=%d, Tag=%d \n Errorstatus=%d \n", rank, num, status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
    }

    MPI_Finalize();
    return 0;
}