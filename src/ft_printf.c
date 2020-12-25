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

	if (!set_info(ptr, &info, ap))
		return (-1);
	if (info.specifier == '%')
		ret = ft_putper(info);
	else if (info.specifier == 'c')
		ret = ft_putchar_info(va_arg(ap, int), info);
	else if (info.specifier == 's')
		ret = ft_putstr_info(va_arg(ap, char *), info);
	else if (info.specifier == 'p')
		ret = ft_putaddr_info(va_arg(ap, void *), info);
	else if (info.specifier == 'd' || info.specifier == 'i')
		ret = ft_putint_info(va_arg(ap, int), info);
	else if (info.specifier == 'u')
		ret = ft_putuint_info(va_arg(ap, unsigned int), info);
	else if (info.specifier == 'x')
		ret = ft_puthex_info(va_arg(ap, unsigned int), 'a', info);
	else if (info.specifier == 'X')
		ret = ft_puthex_info(va_arg(ap, unsigned int), 'A', info);
	else
		ret = -1;
	return (ret);
}

int		ft_printf(const char *format, ...)
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
			len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (len);
}
