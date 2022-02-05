program sendrecv
    implicit none
    include "mpif.h"

    INTEGER :: numprocs, MyRank
    INTEGER :: ierror
    CHARACTER*100 :: Message

    INTEGER :: Status(MPI_Status_Size)

    CALL MPI_Init(ierror)

    CALL MPI_Comm_rank(MPI_COMM_WORLD, MyRank, ierror)
    CALL MPI_Comm_size(MPI_COMM_WORLD, numprocs, ierror)

    IF (MyRank == 0) THEN
        WRITE(Message, "(A,I2)") "A test message, sent from Rank = ", MyRank

        CALL MPI_Send(Message, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, ierror)
    ELSE IF (MyRank == 1) THEN
        CALL MPI_Recv(Message, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD, Status, ierror)

        PRINT "(A,I2,2X,A,A)", "This is in Rank = ", MyRank, "Printing - ", Message
    END IF

    CALL MPI_Finalize(ierror)

end program sendrecv