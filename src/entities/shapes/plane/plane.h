#ifndef RT_CHALLENGE_PLANE_H
#define RT_CHALLENGE_PLANE_H
#include "../../../../heads_global/minirt.h"

typedef struct t_plane
{
}               s_plane;

s_plane     *plane_plane();
s_plane    *plane_defautl();

s_tuple     *plane_normal_at();
void        plane_free(s_plane *pl);

#endif //RT_CHALLENGE_PLANE_H
