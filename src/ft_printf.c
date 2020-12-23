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

int		convert(const char **ptr, va_list it)
{
	int		ret;
	t_info	info;

	set_info(ptr, &info, it);
	if (info.type == '%')
		ret = ft_putper(info);
	else if (info.type == 'c')
		ret = ft_putchar_info(va_arg(it, int), info);
	else if (info.type == 's')
		ret = ft_putstr_info(va_arg(it, char *), info);
	else if (info.type == 'p')
		ret = ft_putaddr_info(va_arg(it, void *), info);
	else if (info.type == 'd' || info.type == 'i')
		ret = ft_putint_info(va_arg(it, int), info);
	else if (info.type == 'u')
		ret = ft_putuint_info(va_arg(it, unsigned int), info);
	else if (info.type == 'x')
		ret = ft_puthex_info(va_arg(it, unsigned int), 'a', info);
	else if (info.type == 'X')
		ret = ft_puthex_info(va_arg(it, unsigned int), 'A', info);
	else
		ret = -1;
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	int len;
	va_list it;
	int ret;

	len = 0;
	va_start(it, format);
	while (*format)
	{
		if (*format == '%')
		{
			if ((ret = convert(&format, it)) == -1)
				return (-1);
			len += ret;
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(it);
	return (len);
}
