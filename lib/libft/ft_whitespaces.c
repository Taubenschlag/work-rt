#include <stdlib.h>

static int present(char c, char *set)
{
    char *set_ptr;

    set_ptr = set;
    while (*set_ptr)
    {
        if (*set_ptr == c)
            return (1);
        set_ptr++;
    }
    return (0);
}

static int	wcount(char *s, char *set)
{
    int	w;

    w = 0;
    while (*s)
    {
        while (*s && present(*s, set))
            s++;
        if (*s && !present(*s, set))
        {
            w++;
            while (*s && !present(*s, set))
                s++;
        }
    }
    return (w);
}

static char	*allocate(char *s, char *set)
{
    char	*word;
    int		chars;

    chars = 0;
    while (s[chars] && !present(s[chars], set))
        chars++;
    if (!(word = malloc(sizeof(char) * (chars + 1))))
        return (NULL);
    word[chars--] = '\0';
    while (chars >= 0)
    {
        word[chars] = s[chars];
        chars--;
    }
    return (word);
}

static char	**split(char const *s)
{
    char	**table;
    char    *set;
    char	*st;
    int		wc;
    int		i;

    set = " \t";
    st = (char *)s;
    i = 0;
    wc = wcount(st, set);
    if ((table = malloc(sizeof(char *) * (wc + 1))))
    {
        while (*st && i < wc)
        {
            while (*st && present(*st, set))
                st++;
            if (*st && !present(*st, set))
            {
                table[i++] = allocate(st, set);
                while (*st && !present(*st, set))
                    st++;
            }
        }
        table[i] = NULL;
    }
    return (table);
}

char		**ft_whitespaces(char const *s)
{
    if (s)
        return (split(s));
    return (NULL);
}