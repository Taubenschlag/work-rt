#include "../heads_global/minirt.h"
#include "service/errs/err.h"
#include "service/files/scene.h"

int main(int ac, char **av)
{
    int fd;
    s_scene *s;
    
    fd = 0;
    if(!(fd = check_input(ac, av)) || fd == -1)
        exit(EXIT_FAILURE);
    else
        s = parse_scene(fd);
    (void)s;
    close(fd);
    return(0);
}
