/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whitespaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:16:10 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/26 00:29:05 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	present(char c, char *set)
{
	char	*set_ptr;

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
	word = malloc(sizeof(char) * (chars + 1));
	if (!word)
		return (NULL);
	word[chars--] = '\0';
	while (chars >= 0)
	{
		word[chars] = s[chars];
		chars--;
	}
	return (word);
}

static char	**split(char const *s, char *set)
{
	char	**table;
	char	*st;
	int		wc;
	int		i;

	st = (char *)s;
	i = 0;
	wc = wcount(st, set);
	table = malloc(sizeof(char *) * (wc + 1));
	if (table)
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

char	**ft_whitespaces(char const *s)
{
	if (s)
		return (split(s, " \t"));
	return (NULL);
}
