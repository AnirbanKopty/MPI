#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, age, weight;
    MPI_Status status;

    // MPI_Initialization
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // code here
    if(rank==0)
    {
        age=30;
        weight=70;
        MPI_Send(&age,    1, MPI_INT, 1, 101, MPI_COMM_WORLD);
        MPI_Send(&weight, 1, MPI_INT, 1, 201, MPI_COMM_WORLD);
        printf("Sent Message: Age=%d Weight=%d\n", age, weight);
    }
    if(rank==1)
    {
        // mistakenly  swapped the tags
        MPI_Recv(&age,    1, MPI_INT, 1, 201, MPI_COMM_WORLD, &status);
        MPI_Recv(&weight, 1, MPI_INT, 1, 101, MPI_COMM_WORLD, &status);
        printf("Received Message: Age=%d Weight=%d", age, weight);
    }

    MPI_Finalize();
    return 0;
}

// The Deadlock is possibly happening here in my system with slower cores
// Usually what we would get is something like
// Sent Message: Age=30 Weight=70
// Received Message: Age=70 Weight=30