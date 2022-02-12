#ifndef RT_CHALLENGE_BMP_H
#define RT_CHALLENGE_BMP_H

#include "../../../heads_global/minirt.h"

typedef struct  t_canvas
{
    unsigned int    w;
    unsigned int    h;
    unsigned int    **canvas;
}               s_canvas;

s_canvas        *canvas_canvas(unsigned int w, unsigned int h);
void            canvas_free(s_canvas *c);
int             init_bmp(int h, int w, int fd);
void            fill_bmp(int fd, s_canvas *c);

#endif //RT_CHALLENGE_BMP_H
