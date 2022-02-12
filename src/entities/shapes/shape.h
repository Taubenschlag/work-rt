#ifndef RT_CHALLENGE_SHAPE_H
#define RT_CHALLENGE_SHAPE_H

#include "../../../heads_global/minirt.h"

typedef struct      t_shape
{
    char type;
    s_matrl *matrl;
    s_matrix *trans;
    void *shape;

}                   s_shape;

// static unsigned int g_id;

s_shape             *make_shape(char type, void *shape_itself);
s_shape             *test_shape();
void                *set_transform(s_shape *sh, s_matrix *trans);//todo deprecated
s_tuple             *shape_normal_at(s_shape *sh, s_tuple *p);
void                free_shape(s_shape *s);

#endif