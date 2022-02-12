#ifndef SCENE_H
# define SCENE_H

#include "../../../heads_global/minirt.h"

#define COLOR_CF 0.003921569

typedef struct  t_scene
{
    int         resolution_x;
    int         resolution_y;
    double      ambi_ratio;
    s_tuple     *ambi_color;
    int         camera_counter;
    s_camera    **cameras;
    int         light_counter;
    s_light     **lights;
    int         shape_counter;
    s_shape     **shapes;
}               s_scene;

s_tuple         *get_tuple(char *value, char type);
void            free_scene(s_scene *s);
int             handle_r(char *line, s_scene *s);
int             handle_a(char *line, s_scene *s);
int             handle_c(char *line, s_scene *s, char *name);
int             handle_l(char *line, s_scene *s);
int             handle_shape(char *line, s_scene *s);
int             handle_plane(char **values, s_scene *s);
int             handle_sphere(char **values, s_scene *s);
int             handle_square(char **values, s_scene *s);
int             handle_cylinder(char **values, s_scene *s);
int             handle_triangle(char **values, s_scene *s);
int             handle_cone(char **values, s_scene *s);
int             handle_cube(char **values, s_scene *s);
void            save_scene(s_scene *s);
s_scene         *parse_scene(int fd, int *counters);
void            cleanup(char **values);

#endif