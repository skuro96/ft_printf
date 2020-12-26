/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skurosu <skurosu@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:47:04 by skurosu           #+#    #+#             */
/*   Updated: 2020/12/26 01:47:07 by skurosu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*format_uint(unsigned int n, t_info info)
{
	char	*tmp;
	char	*zeros;
	char	*ret;
	int		size;
	int		i;

	if (info.dot && info.precision == 0 && n == 0)
		return (ft_strdup(""));
	if (!info.dot || info.precision < digits(n))
		return (ft_itoa_us(n));
	size = info.precision - digits(n);
	if (!(zeros = malloc(size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
		zeros[i++] = '0';
	zeros[i] = '\0';
	tmp = ft_itoa_us(n);
	ret = ft_strjoin(zeros, tmp);
	return (freeturn(&zeros, &tmp, ret));
}

static int	ft_putuint_width(t_info info, char *num_str)
{
	int len;
	int	dig;

	dig = ft_strlen(num_str);
	len = 0;
	if (info.zero && !info.dot)
	{
		while (len < info.width - dig)
			len += ft_putchar('0');
		len += ft_putstr(num_str);
	}
	else
	{
		len += (info.minus ? ft_putstr(num_str) : 0);
		while (len < info.width - (info.minus ? 0 : dig))
			len += ft_putchar(' ');
		len += (info.minus ? 0 : ft_putstr(num_str));
	}
	return (len);
}

int			ft_putuint_info(unsigned int n, t_info info)
{
	char	*num_str;
	int		len;

	if (!(num_str = format_uint(n, info)))
		return (-1);
	len = 0;
	if (info.width >= 0)
		len += ft_putuint_width(info, num_str);
	else
		len += ft_putstr(num_str);
	free(num_str);
	return (len);
}
