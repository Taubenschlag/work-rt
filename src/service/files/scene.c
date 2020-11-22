#include "scene.h"

s_scene         *make_scene()
{
    s_scene *ret;

    ret = malloc(sizeof(s_scene));
    ret->resolution_x = -1;
    ret->resolution_y = -1;
    ret->ambi_ratio = -1;
    ret->camera_counter = 0;
    ret->lights_counter = 0;
    ret->shape_counter = 0;
    return (ret);
}

// int             check_line(char *line, s_scene *s)
// {
//     char    **values;

//     values = ft_split(line, ' ');

//     return 1;
// }

s_scene         *parse_scene(int fd)
{
    char    *line;
    s_scene *sc;

    sc = make_scene();
    if(get_next_line(fd, &line) && handle_r(line, sc) &&
        get_next_line(fd, &line) && handle_a(line, sc))
        return (sc);
    // while (get_next_line(fd, &line))
    //     if(!check_line(line, sc))
    //         return NULL;
    return NULL;
}

void            free_scene(s_scene *s)
{
    (void)s;
}