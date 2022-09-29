#include "../heads_global/minirt.h"

int main(int ac, char **av)
{
    int fd;
    s_scene *s;
    int *counters;
    
    if((fd = check_arguments(ac, av)) < 1 ||
        !(counters = check_file(ac == 2? av[1]:av[2])))
        exit(EXIT_FAILURE);
    else
        s = parse_scene(fd, counters);
    free(counters);
    close(fd);
    if (ac == 3)
        save_scene(s);
    else
        display_scene(s);
    return(0);
}
