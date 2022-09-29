/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_non_zero.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:26:40 by rokupin           #+#    #+#             */
/*   Updated: 2020/01/22 12:04:19 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit_non_zero(int c)
{
	if (c > '0' && c <= '9')
		return (1);
	return (0);
}
