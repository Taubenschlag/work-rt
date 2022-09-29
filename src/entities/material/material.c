#include "../../../heads_global/minirt.h"

s_matrl *material_make(
        s_tuple *color,
        double diffuse,
        double ambient,
        double specular,
        double shininess)
{
    s_matrl *res;

    res = (s_matrl*)malloc(sizeof(s_matrl));
    res->color = color;
    res->ambient = ambient;
    res->diffuse = diffuse;
    res->shininess = shininess;
    res->specular = specular;
    return (res);
}

s_matrl *material_make_default()
{
    return (material_make(
            NULL,
            0.9, 0.1, 0.9, 200));
}

s_matrl *mat_with_col(s_tuple *color)
{
    return (material_make(
            color,
            0.9, 0.1, 0.9, 200));
}

void    material_free(s_matrl *m)
{
    tuple_free(m->color);
    free(m);
}

