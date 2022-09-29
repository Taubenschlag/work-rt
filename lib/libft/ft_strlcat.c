/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coop <coop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:03:22 by rokupin           #+#    #+#             */
/*   Updated: 2019/12/21 12:29:24 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char *str, int len)
{
	int	i;

	i = 0;
	if (str)
		while (i < len && str[i])
			i++;
	return ((size_t)i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	srcln;
	size_t	dstln;

	j = 0;
	srcln = ft_strlen(src);
	if (dstsize < 1)
		return (srcln);
	dstln = ft_strnlen(dst, dstsize);
	i = dstln;
	while (dstsize && src[j] && i < dstsize - 1)
		dst[i++] = src[j++];
	if (j)
		dst[i] = '\0';
	return (ft_strlen(src) + dstln);
}
