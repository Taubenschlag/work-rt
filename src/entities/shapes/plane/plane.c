#include "../../../../heads_global/minirt.h"

s_plane *plane_plane()
{
    s_plane *plane;

    plane = (s_plane*)malloc(sizeof(s_plane));
    return (plane);
}

s_plane    *plane_defautl()
{
    return (plane_plane());
}

s_tuple     *plane_normal_at()
{
    return (tuple_vector(0, 1, 0));
}

void        plane_free(s_plane *pl)
{
    free(pl);
}
