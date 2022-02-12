#ifndef RT_CHALLENGE_MATERIAL_H
#define RT_CHALLENGE_MATERIAL_H

#include "../../../heads_global/minirt.h"


typedef struct      t_matrl
{
    s_tuple *color;
    double diffuse;
    double ambient;
    double specular;
    double shininess;
}                   s_matrl;

typedef struct      t_lightning_pack
{
    s_matrl *m;
    s_light *l;
    s_tuple *posit;
    s_tuple *eye_v;
    s_tuple *norm_v;
    s_tuple *ef_color;
    s_tuple *lightv;
    s_tuple *diffuse;
    s_tuple *specular;
    double  light_dot_norm;
}                  s_lightning_pack;

s_matrl             *material_make(
                                s_tuple *color,
                                double diffuse,
                                double ambient,
                                double specular,
                                double shininess);
s_matrl             *material_make_default();
void                material_free(s_matrl *m);
s_lightning_pack    *make_l_p(s_matrl *m,
                                s_light *l,
                                s_tuple *posit,
                                s_tuple *eye_v,
                                s_tuple *norm_v);
s_tuple             *lightning(s_lightning_pack *p, int in_shadow);
void                cleanup_light_pack(s_lightning_pack *l);
s_matrl             *mat_with_col(s_tuple *color);

#endif //RT_CHALLENGE_MATERIAL_H
