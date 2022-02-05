program MPI_Ex
    implicit none
    include '/home/anirbankopty/Softwares/MPICH/mpich-install/include/mpif.h'

    INTEGER :: rank, size, ierror
    call MPI_Init(ierror)
    call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierror)
    call MPI_Comm_size(MPI_COMM_WORLD, size, ierror)

    PRINT "(A,I2,A,I2)", "Hello world! I'm ", rank, " of ", size

    call MPI_Finalize()

end program MPI_Ex