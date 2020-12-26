/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skurosu <skurosu@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:49:17 by skurosu           #+#    #+#             */
/*   Updated: 2020/12/26 01:49:47 by skurosu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_hex(unsigned int n, char a_size)
{
	char	*dest;
	int		len;
	int		i;

	len = digits_base(n, 16);
	if (!(dest = malloc(len + 1)))
		return (NULL);
	i = len - 1;
	while (i >= 0)
	{
		dest[i] = n % 16 + (n % 16 < 10 ? '0' : a_size - 10);
		n /= 16;
		i--;
	}
	dest[len] = '\0';
	return (dest);
}

static char	*format_hex(unsigned int n, char a_size, t_info info)
{
	int		zsize;
	char	*zeros;
	char	*tmp;
	char	*ret;
	int		i;

	if (info.dot && info.precision == 0 && n == 0)
		return (ft_strdup(""));
	zsize = info.precision - digits_base(n, 16);
	zsize = (zsize < 0 ? 0 : zsize);
	if (!(zeros = malloc(zsize + 1)))
		return (NULL);
	i = 0;
	while (i < zsize)
		zeros[i++] = '0';
	zeros[i] = '\0';
	tmp = ft_itoa_hex(n, a_size);
	ret = ft_strjoin(zeros, tmp);
	return (freeturn(&zeros, &tmp, ret));
}

static int	ft_puthex_width(t_info info, char *num_str)
{
	int len;
	int dig;

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
		while (len < (info.minus ? info.width : info.width - dig))
			len += ft_putchar(' ');
		len += (info.minus ? 0 : ft_putstr(num_str));
	}
	return (len);
}

int			ft_puthex_info(unsigned int n, char a_size, t_info info)
{
	char	*num_str;
	int		len;

	if (!(num_str = format_hex(n, a_size, info)))
		return (0);
	len = 0;
	if (info.width >= 0)
		len += ft_puthex_width(info, num_str);
	else
		len += ft_putstr(num_str);
	free(num_str);
	return (len);
}
