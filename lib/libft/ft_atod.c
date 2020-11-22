#include "libft.h"

int	get_range(long n, int negative)
{
    int		range;

    range = 1 + negative;
    while (n >= 10)
    {
        n /= 10;
        range++;
    }
    return (range);
}

double      ft_atod(char *str)
{
    int f;
    double s;
    int div;
    double res;
    int negative;

    f = ft_atoi(str);
    f = f < 0 ? f * -1 : f;
    negative = str[0] == '-';
    div = get_range((long)f, negative);
    str += sizeof(char) * (div + 1);
    s = (double)ft_atoi(str);
    div = get_range((long)s, 0);
    while (--div >= 0)
        s /= 10;
    res = (double)(s + f);
    if (negative)
        res *= -1;
    return (res);
}