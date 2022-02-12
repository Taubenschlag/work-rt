#include "../heads_global/minirt.h"

int     min(int a, int b)
{
    return (a < b ? a : b);
}

int     max(int a, int b)
{
    return (a > b ? a : b);
}

double     max_d(double a, double b)
{
    return (a > b ? a : b);
}

void    swap(double *x, double *y)
{
    double sw;

    sw = *x;
    *x = *y;
    *y = sw;
}

double     mins(double *a, int length)
{
    int i;
    double min;

    min = INFINITY * 1;
    i = -1;
    while (++i < length)
    {
       if( a[i] < min)
           min = a[i];
    }
    return (min);
}

double     maxs(double *a, int length)
{
    int i;
    double max;

    max = INFINITY * -1;
    i = -1;
    while (++i < length)
    {
        if( a[i] > max)
            max = a[i];
    }
    return (max);
}