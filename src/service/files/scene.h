#ifndef SCENE_H
# define SCENE_H

#include "../../../heads_global/minirt.h"

typedef struct  t_scene
{
    int         resolution_x;
    int         resolution_y;
    double      ambi_ratio;
    s_tuple     *ambi_color;
    int         camera_counter;
    // s_camera    **cameras;
    int         lights_counter;
    // s_light     **lights;
    int         shape_counter;
    // s_shape     **shapes;
}               s_scene;

s_scene         *make_scene();
s_scene         *parse_scene(int fd);
void            free_scene(s_scene *s);
int             handle_r(char *line, s_scene *s);
int             handle_a(char *line, s_scene *s);
// int             handle_c(char **input, s_scene *s);
// int             handle_l(char **input, s_scene *s);
// int             handle_shape(char **input, s_scene *s);

#endif