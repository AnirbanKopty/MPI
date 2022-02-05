program test
    implicit none
    CHARACTER(100) :: message
    INTEGER :: anum = 15

    WRITE(message, *) "Testing storing message in Fortran", anum

    PRINT *, trim(message), "<--"

    
end program test