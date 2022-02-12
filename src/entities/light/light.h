#ifndef RT_CHALLENGE_LIGHT_H
#define RT_CHALLENGE_LIGHT_H

#include "../../../heads_global/minirt.h"


typedef struct  t_light
{
    s_tuple     *position;
    s_tuple     *color;
}               s_light;

s_light     *light_make(s_tuple *position, s_tuple  *color);
void        light_free(s_light *l);

#endif
