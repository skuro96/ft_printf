/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skurosu <skurosu@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:52:50 by skurosu           #+#    #+#             */
/*   Updated: 2020/12/26 02:00:49 by skurosu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert(const char **ptr, va_list ap)
{
	t_info	info;

	if (!set_info(ptr, &info, ap))
		return (-1);
	if (info.specifier == '%')
		return (ft_putchar_info('%', info));
	if (info.specifier == 'c')
		return (ft_putchar_info(va_arg(ap, int), info));
	if (info.specifier == 's')
		return (ft_putstr_info(va_arg(ap, char *), info));
	if (info.specifier == 'p')
		return (ft_putaddr_info(va_arg(ap, void *), info));
	if (info.specifier == 'd' || info.specifier == 'i')
		return (ft_putint_info(va_arg(ap, int), info));
	if (info.specifier == 'u')
		return (ft_putuint_info(va_arg(ap, unsigned int), info));
	if (info.specifier == 'x')
		return (ft_puthex_info(va_arg(ap, unsigned int), 'a', info));
	if (info.specifier == 'X')
		return (ft_puthex_info(va_arg(ap, unsigned int), 'A', info));
	return (-1);
}

int			ft_printf(const char *format, ...)
{
	int		len;
	int		ret;
	va_list	ap;

	va_start(ap, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if ((ret = convert(&format, ap)) == -1)
				return (-1);
			len += ret;
		}
		else
			len += ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (len);
}
