/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:19 by vlugand-          #+#    #+#             */
/*   Updated: 2019/12/22 16:28:33 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_strdup( char *s1)
{
    char		*s2;
    size_t		i;

    i = 0;
    while (s1[i])
        i += 1;
    if (!(s2 = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    i = -1;
    while (s1[++i])
        s2[i] = s1[i];
    s2[i] = '\0';
    return (s2);
}

static char	*ft_strjoin(char *s1, char *s2)
{
    long l1;
    long l2;
    char *res;

    l1 = 0;
    l2 = 0;
    if (!s1 || !s2)
        return (NULL);
    while (s1[l1])
        l1++;
    while (s2[l2])
        l2++;
    res = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
    if (!res)
        return (NULL);
    res[l1 + l2] = '\0';
    while (--l2 >= 0)
        res[l1 + l2] = s2[l2];
    while (--l1 >= 0)
        res[l1] = s1[l1];
    free(s1);
    return (res);
}

static int			gnl_verify_line(char **stack, char **line)
{
    char			*tmp_stack;
    char			*strchr_stack;
    int				i;

    i = 0;
    strchr_stack = *stack;
    while (strchr_stack[i] != '\n')
        if (!strchr_stack[i++])
            return (0);
    tmp_stack = &strchr_stack[i];
    *tmp_stack = '\0';
    tmp_stack = ft_strdup(tmp_stack + 1);
    *line = ft_strdup(*stack);
    free(*stack);
    *stack = ft_strdup(tmp_stack);
    free(tmp_stack);
    return (1);
}

static	int			gnl_read_file(int fd, char *heap, char **stack, char **line)
{
    int				ret;

    while ((ret = read(fd, heap, BUFF_SIZE)) > 0)
    {
        heap[ret] = '\0';
        if (*stack)
        {
            *stack = ft_strjoin(*stack, heap);
        }
        else
            *stack = ft_strdup(heap);
        if (gnl_verify_line(stack, line))
            break ;
    }
    return (RET_VALUE(ret));
}

int					get_next_line(int const fd, char **line)
{
    static char		*stack[MAX_FD];
    char			*heap;
    int				ret;
    int				i;

    if (!line || (fd < 0 || fd >= MAX_FD) || (read(fd, stack[fd], 0) < 0) \
		|| !(heap = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
        return (-1);
    if (stack[fd])
        if (gnl_verify_line(&stack[fd], line))
            return (1);
    i = 0;
    while (i < BUFF_SIZE)
        heap[i++] = '\0';
    ret = gnl_read_file(fd, heap, &stack[fd], line);
    free(heap);
    if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
    {
        if (!ret && *line)
            *line = 0;
        return (ret);
    }
    *line = stack[fd];
    stack[fd] = NULL;
    return (1);
}