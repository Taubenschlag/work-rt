/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 21:48:17 by rokupin           #+#    #+#             */
/*   Updated: 2020/01/22 12:13:49 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(char *s, int len)
{
	int		l;
	char	*ret;

	l = ft_strlen(s);
	if (len > l)
		len = l;
	l = 0;
	ret = malloc(sizeof(char) * (len + 1));
	while (l < len && s[l])
	{
		ret[l] = s[l];
		l++;
	}
	ret[l] = '\0';
	return (ret);
}
