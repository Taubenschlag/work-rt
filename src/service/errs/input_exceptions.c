#include "../../../heads_global/minirt.h"

int    check_input(int ac, char **av)
{
    int fd;
    
    fd = 0;
    if (ac == 1 || ac > 3 ||
        (ac == 3 && 
        !((ft_strequals(av[1], "--save")) && (fd = open(av[2], O_RDONLY)))) ||
        (ac == 2 &&
        !(fd = open(av[1], O_RDONLY))))
    {
        perror("wrong argument");
        return (-1);
    }
    if (fd == -1)
    {
        perror("file not found");
        return (-1);
    }
    return (fd);
} 