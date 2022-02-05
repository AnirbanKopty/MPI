#include <stdio.h>
#include <mpi.h>

#define BUFFER_SIZE 20    // The element size to be sent

int main(argc, argv)
int argc; char *argv[];
{
    int MyRank, Numprocs, Destination, Source, iproc;
    int Destination_tag, Source_tag;
    char Message[BUFFER_SIZE];
    // Status datatype - required in MPI Receive call
    MPI_Status status;

    // MPI_Initialization
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

    // Main section of Message Passing
    if(MyRank != 0)
    {
        sprintf(Message, "Hello World from %d", MyRank);
        // Message = "Hello World"
        Destination = 0;
        Destination_tag = 0;

        // Sending message
        MPI_Send(Message, BUFFER_SIZE, MPI_CHAR, Destination, Destination_tag, MPI_COMM_WORLD);

    }
    else
    {
        for(iproc = 1; iproc < Numprocs; iproc++)
        {
            Source = iproc;
            Source_tag = 0;

            // Receiving message
            MPI_Recv(Message, BUFFER_SIZE, MPI_CHAR, Source, Source_tag, MPI_COMM_WORLD, &status);

            printf("%s : Received from rank = %d\n", Message, iproc);

        }
    }

    // Terminating the MPI
    MPI_Finalize();
    return 0;
}