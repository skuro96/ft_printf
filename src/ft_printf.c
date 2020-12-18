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
	int len;
	t_info info;

	len = 0;
	set_info(ptr, &info, it);
	if (info.type == '%')
		len += ft_putper(info);
	else if (info.type == 'c')
		len += ft_putchar_info(va_arg(it, int), info);
	else if (info.type == 's')
		len += ft_putstr_info(va_arg(it, char *), info);
	else if (info.type == 'p')
		len += ft_putaddr_info(va_arg(it, void *), info);
	else if (info.type == 'd' || info.type == 'i')
		len += ft_putint_info(va_arg(it, int), info);
	else if (info.type == 'u')
		len += ft_putuint_info(va_arg(it, unsigned int), info);
	else if (info.type == 'x')
		len += ft_puthex_info(va_arg(it, unsigned int), 'a', info);
	else if (info.type == 'X')
		len += ft_puthex_info(va_arg(it, unsigned int), 'A', info);
	return (len);
}

int		ft_printf(const char *format, ...)
{
	int len;
	va_list it;

	len = 0;
	va_start(it, format);
	while (*format)
	{
		if (*format == '%')
			len += convert(&format, it);
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(it);
	return (len);
}
