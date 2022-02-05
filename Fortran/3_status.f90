program status
    implicit none
    include "mpif.h"
    
    INTEGER :: MyRank, ierror, num
    INTEGER :: stats(MPI_Status_Size)

    CALL MPI_Init(ierror)

    CALL MPI_Comm_rank(MPI_COMM_WORLD, MyRank, ierror)

    IF (MyRank == 0) THEN
        num = 309845
        CALL MPI_Send(num, 1, MPI_INT, 1, 101, MPI_COMM_WORLD, ierror)
        ! Size = 1, cause it's the size of the number of elements in an array, not the storage size of the variable
        PRINT *, "Sender side Rank = ", MyRank
    
    ELSE IF (MyRank == 1) THEN
        CALL MPI_Recv(num, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, stats, ierror)
        PRINT *, "Receiver side Rank =", MyRank, ", Num = ", num , ", Source = ", stats(MPI_SOURCE), ", Tag = ",stats(MPI_TAG)
        PRINT *, "Error Status = ", stats(MPI_ERROR)
    END IF

    CALL MPI_Finalize(ierror)
end program status