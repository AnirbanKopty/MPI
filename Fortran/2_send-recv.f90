program SendRecv
    implicit none
    ! include "/home/anirbankopty/Softwares/MPICH/mpich-install/include/mpif.h"
    include "mpif.h"

    INTEGER, PARAMETER :: Buffer_Size = 50

    INTEGER :: MyRank, Numprocs, Destination, Source, iproc
    INTEGER :: Destination_tag, Source_tag, ierr
    CHARACTER*50 :: Message
    ! Status Datatype - required in MPI Receive Call
    INTEGER :: status(MPI_Status_Size)
    
    ! MPI Initialization
    CALL MPI_Init(ierr)

    CALL MPI_Comm_rank(MPI_COMM_WORLD, MyRank, ierr)
    CALL MPI_Comm_size(MPI_COMM_WORLD, Numprocs, ierr)

    ! Main section of Message Passing
    IF (MyRank .NE. 0) THEN
        write(Message,"(A,I2)") "Hello World from ", MyRank

        Destination = 0;
        Destination_tag = 0;

        ! Sending message
        CALL MPI_Send(Message, BUFFER_SIZE, MPI_CHAR, Destination, Destination_tag, MPI_COMM_WORLD, ierr);

    ELSE
        DO iproc = 1, Numprocs-1
            Source = iproc;
            Source_tag = 0;

            ! Receiving message
            CALL MPI_Recv(Message, BUFFER_SIZE, MPI_CHAR, Source, Source_tag, MPI_COMM_WORLD, status, ierr);

            PRINT "(A, A, I2)", TRIM(Message), " : Received from rank = ", iproc
        END DO
    END IF

    ! Terminating the MPI
    CALL MPI_Finalize(ierr) 
    
end program SendRecv