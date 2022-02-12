#ifndef RT_CHALLENGE_CYLINDER_H
#define RT_CHALLENGE_CYLINDER_H

#include "../../../../heads_global/minirt.h"

typedef struct t_cylinder
{
    double min;
    double max;
    int closed;
}               s_cylinder;

s_cylinder  *cylinder_cylinder();
s_cylinder  *cylinder_params(double h);
s_tuple     *cylinder_normale_at(s_tuple *t, s_cylinder *c);
int         check_cap(s_ray *r, double t);
void        cylinder_free(s_cylinder *c);

#endif //RT_CHALLENGE_CYLINDER_H
