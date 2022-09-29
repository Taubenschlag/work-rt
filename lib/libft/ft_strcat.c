/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 12:48:38 by rokupin           #+#    #+#             */
/*   Updated: 2020/01/22 12:11:39 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcat(char *src, char *dst)
{
	int		i;
	int		j;
	char	*ret;

	if (!src)
		return (dst);
	if (!dst)
		return (src);
	i = 0;
	j = 0;
	while (src[i])
		i++;
	while (dst[j])
		j++;
	ret = malloc(sizeof(char) * (i + j + 1));
	ret[i + j] = '\0';
	while (--i >= 0)
		ret[i + j] = src[i];
	while (--j >= 0)
		ret[j] = dst[j];
	free(src);
	free(dst);
	return (ret);
}
