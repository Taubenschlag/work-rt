int ft_strequals(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (!s1[i] && !s2[i])
        return (1);
    return (0);
}