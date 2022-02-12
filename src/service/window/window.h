#include "../../../heads_global/minirt.h"

typedef struct  t_mlx_wrap {
    void        *mlx;
    void        *win;
    void        **imgs;
    char        **addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int         img_ptr;
    int         img_counter;
}               s_mlx_wrap;

s_canvas        *argb_render(s_camera *c, s_world *w);
void            my_mlx_pixel_put(s_mlx_wrap *data,  unsigned int x,  unsigned int y, int color, int count);
void            fill_image(s_canvas *c, s_mlx_wrap *data, int count);
void            display_scene(s_scene *s);
//int             wclose(int keycode, s_mlx_win *vars);