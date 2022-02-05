program MPIEx
    implicit none
    include 'mpif.h'

    INTEGER :: rank, size, ierror
    call MPI_Init(ierror)
    call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierror)
    call MPI_Comm_size(MPI_COMM_WORLD, size, ierror)
    
    PRINT *, "Hello World! I'm ", rank, " of ", size

    call MPI_Finalize()

end program MPIEx