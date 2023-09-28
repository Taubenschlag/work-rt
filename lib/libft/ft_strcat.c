/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:10:11 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/22 09:31:54 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcat(char *src, char *dst)
{
	char	*ret;
	int		i;
	int		j;

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
