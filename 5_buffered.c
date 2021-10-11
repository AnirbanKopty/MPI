#include <stdio.h>
#include <stdlib.h>     // for the system
#include <unistd.h>     // for the sleep
#include <mpi.h>

#define N 100000

int main(int argc, char **argv)
{
    int rank, i, a[N], buf[N+100];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Create extra MPI buffer
    MPI_Buffer_attach(buf, 4*(N+100));
    // parameters: buf (buffer array), Size (4 cause Integer data type is 4 bytes)
    // MPI_Bsend to be used

    if(rank==0)
    {
        for(i=0;i<N;i++)
            a[i]=i;
        // Below is a shell code
        system("echo -n Time before send call : ; date");

        // MPI Buffered Send
        MPI_Bsend(a, N, MPI_INT, 1, 101, MPI_COMM_WORLD);

        system("echo -n Time after send call : ; date");
    }

    if(rank==1)
    {
        // Delay introduced at receiver side
        sleep(5);
        MPI_Recv(a, N, MPI_INT, 0, 101, MPI_COMM_WORLD, &status);
    }

    MPI_Finalize();
    return 0;
}

// Here if the buffer size is lower compared to the data size,
//we can notice the wait time. (see for N=100000)

// for that purpose, we can define our own buffer size. (See line :16)
// here we need to use MPI_Bsend()