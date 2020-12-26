/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skurosu <skurosu@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:52:50 by skurosu           #+#    #+#             */
/*   Updated: 2020/12/26 16:12:53 by skurosu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert(const char **ptr, va_list ap, int left)
{
	int		ret;
	t_info	info;

	if (!set_info(ptr, &info, ap))
		return (-1);
	if (left < info.width || (info.dot && left < info.precision))
		return (-1);
	if (info.spec == '%')
		ret = ft_putchar_info('%', info);
	if (info.spec == 'c')
		ret = ft_putchar_info(va_arg(ap, int), info);
	if (info.spec == 's')
		ret = ft_putstr_info(va_arg(ap, char *), info);
	if (info.spec == 'p')
		ret = ft_putaddr_info(va_arg(ap, void *), info);
	if (info.spec == 'd' || info.spec == 'i')
		ret = ft_putint_info(va_arg(ap, int), info);
	if (info.spec == 'u')
		ret = ft_putuint_info(va_arg(ap, unsigned int), info);
	if (info.spec == 'x' || info.spec == 'X')
		ret = ft_puthex_info(va_arg(ap, unsigned int), info.spec - 23, info);
	if (ret == -1 || ret > left)
		return (-1);
	return (ret);
}

int			ft_printf(const char *format, ...)
{
	int		len;
	int		left;
	int		ret;
	va_list	ap;

	va_start(ap, format);
	len = 0;
	while (*format)
	{
		left = INT_MAX - len - 1;
		if (*format == '%')
		{
			if ((ret = convert(&format, ap, left)) == -1)
				return (-1);
			len += ret;
		}
		else if (left < 1)
			return (-1);
		else
			len += ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (len);
}
