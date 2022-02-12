#ifndef RT_CHALLENGE_SQUARE_H
#define RT_CHALLENGE_SQUARE_H
#include "../../../../heads_global/minirt.h"

typedef struct t_square
{
    s_triangle *t1;
    s_triangle *t2;
}               s_square;

s_square      *square();
s_tuple       *square_normale_at();
void          free_square(s_square *t);

#endif //RT_CHALLENGE_SQUARE_H
