#include "scene.h"

int handle_r(char *line, s_scene *s)
{
    int i;
    char **input;

    input = ft_split(line, ' ');
    i = -1;
    if (input && ft_strequals(input[0],"R"))
    {
        if (s->resolution_x < 0)
        {
            s->resolution_x = ft_atoi(input[1]);
            s->resolution_y = ft_atoi(input[2]);
        }
        else
        {
            while (input[++i])
                free(input[i]);
            free(input);
            return (0);
        }
    }
    while (input[++i])
        free(input[i]);
    free(input);
    return (s->resolution_x > 0 && s->resolution_y > 0);
}

int handle_a(char *line, s_scene *s)
{
    int i;
    char **input;
    char **next_part;

    input = ft_split(line, ' ');
    i = -1;
    if (input && ft_strequals(input[0],"A"))
    {
        if (s->ambi_ratio < 0)
            s->ambi_ratio = ft_atod(input[1]);
        else
            s->ambi_ratio = -1;
        next_part = ft_split(input[2], ',');
        s->ambi_color = tuple_color(
            ft_atoi(next_part[0]),ft_atoi(next_part[1]), ft_atoi(next_part[2]));
            while (next_part[++i])
                free(next_part[i]);
            free(next_part);
            i = -1;
    }
    while (input[++i])
        free(input[i]);
    free(input);
    return (s->ambi_ratio >= 0 && s->ambi_ratio <= 1);
}

// int handle_c(char **input, s_scene *s)
// {

// }

// int handle_l(char **input, s_scene *s)
// {

// }

// int handle_shape(char **input, s_scene *s)
// {

// }