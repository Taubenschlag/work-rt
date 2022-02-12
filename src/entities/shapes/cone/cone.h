#ifndef RT_CHALLENGE_CONE_H
#define RT_CHALLENGE_CONE_H

#include "../../../../heads_global/minirt.h"

typedef struct t_cone
{
    double min;
    double max;
    int closed;
}               s_cone;

s_cone          *cone_cone();
s_cone          *cone_param(double h);
s_tuple         *cone_normale_at(s_tuple *t, s_cone *c);
int             check_cap_cone_max(s_ray *r, double t, double max);
int             check_cap_cone_min(s_ray *r, double t, double min);

#endif //RT_CHALLENGE_CONE_H
