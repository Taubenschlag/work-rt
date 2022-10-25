/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:21:22 by rokupin           #+#    #+#             */
/*   Updated: 2021/11/05 23:01:41 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int	*ptr;

	ptr = b;
	while (len > 0)
	{
		*(ptr++) = (unsigned char)c;
		len--;
	}
	return (b);
}
