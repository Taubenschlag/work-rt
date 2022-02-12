#ifndef RT_CHALLENGE_CUBE_H
#define RT_CHALLENGE_CUBE_H
#include "../../../../heads_global/minirt.h"

typedef struct t_cube
{

}               s_cube;


s_cube      *cube_cube();
void        cube_free(s_cube *c);
s_tuple *cube_normal_at(s_tuple *p);

#endif //RT_CHALLENGE_CUBE_H
