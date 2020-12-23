#include "ft_printf.h"

int		ft_putper(t_info info)
{
	int	len;
	int	c;

	c = (info.zero && !info.minus ? '0' : ' ');
	len = 0;
	if (info.minus)
		len += ft_putchar('%');
	while (len < info.width - 1)
		len += ft_putchar(c);
	return (len += (info.minus ? ft_putchar(' '): ft_putchar('%')));
}

int		convert(const char **ptr, va_list ap)
{
	int		ret;
	t_info	info;

	set_info(ptr, &info, ap);
	if (info.type == '%')
		ret = ft_putper(info);
	else if (info.type == 'c')
		ret = ft_putchar_info(va_arg(ap, int), info);
	else if (info.type == 's')
		ret = ft_putstr_info(va_arg(ap, char *), info);
	else if (info.type == 'p')
		ret = ft_putaddr_info(va_arg(ap, void *), info);
	else if (info.type == 'd' || info.type == 'i')
		ret = ft_putint_info(va_arg(ap, int), info);
	else if (info.type == 'u')
		ret = ft_putuint_info(va_arg(ap, unsigned int), info);
	else if (info.type == 'x')
		ret = ft_puthex_info(va_arg(ap, unsigned int), 'a', info);
	else if (info.type == 'X')
		ret = ft_puthex_info(va_arg(ap, unsigned int), 'A', info);
	else
		ret = -1;
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	int		len;
	int		ret;
	int		left;

	va_list	ap;
	left = INT_MAX;
	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			if ((ret = convert(&format, ap, left)) == -1)
				return (-1);
			len += ret;
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (len);
}
