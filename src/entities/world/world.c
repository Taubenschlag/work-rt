#include "../../../heads_global/minirt.h"

s_world *make_world(s_shape **shapes,
        s_light **lights, int shape_counter, int light_counter)
{
    s_world *w;

    w = (s_world*)malloc(sizeof(s_world));
    w->shapes = shapes;
    w->lights = lights;
    w->lights_counter = light_counter;
    w->shape_counter = shape_counter;
    w->ambienace = NULL;
    return (w);
}

s_world     *make_default_world()
{
    s_shape **shapes;
    s_nsphere *s1;
    s_nsphere *s2;
    s_light **lights;

    shapes = (s_shape **)malloc(sizeof(s_shape*) * 2);

    s1 = nsphere_unit(tuple_point(0, 0, 0));
    s2 = nsphere_unit(tuple_point(0, 0, 0));
    shapes[0] = make_shape('s', s1);
    shapes[1] = make_shape('s', s2);
    shapes[0]->matrl = material_make_default();
    shapes[1]->matrl = material_make_default();
    shapes[0]->matrl->specular = 0.2;
    shapes[0]->matrl->diffuse = 0.7;
    shapes[0]->matrl->color = tuple_color(0.8, 1.0 ,0.6);
    set_transform(shapes[1],  matrix_scale(0.5, 0.5 ,0.5));
    lights = (s_light**)malloc(sizeof(s_light*));
    *lights = light_make(tuple_point(-10, 10, -10),
            tuple_color(1, 1 ,1));
    return (make_world(shapes, lights, 2, 1));
}

void        free_world_deep(s_world *w)
{
    while (--(w->shape_counter) >= 0)
        free_shape(w->shapes[w->shape_counter]);
    while (--(w->lights_counter) >= 0)
        light_free(w->lights[w->lights_counter]);
    if (w->ambienace)
        light_free(w->ambienace);
    free(w->shapes);
    free(w->lights);
    free(w);
}

void        world_set_ambience(s_world *w, s_tuple *from, s_tuple *color)
{
    if (w->ambienace)
        light_free(w->ambienace);
    w->ambienace = light_make(tuple_point(from->x,from->y,from->z),
            tuple_color(color->x, color->y, color->z));
}