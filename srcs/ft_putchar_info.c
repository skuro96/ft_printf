/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skurosu <skurosu@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:55:02 by skurosu           #+#    #+#             */
/*   Updated: 2020/12/26 01:55:10 by skurosu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putchar_info(char c, t_info info)
{
	int	len;
	int	space;

	if (info.width == INT_MAX)
		return (-1);
	space = (info.zero ? '0' : ' ');
	len = 0;
	len += (info.minus ? ft_putchar(c) : 0);
	while (len < (info.minus ? info.width : info.width - 1))
		len += ft_putchar(space);
	len += (info.minus ? 0 : ft_putchar(c));
	return (len);
}
