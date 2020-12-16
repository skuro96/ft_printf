#include "ft_printf.h"

int		ft_putstr_info(char *src, t_info info)
{
	char *str;
	int len;

	if (!src)
		str = ft_strdup("(null)"); // free;
	else
		str = src;
	len = 0;
	if (info.dot) // 精度よりもフィールド幅優先
	{
		while (len < info.precision && len < ft_strlen(str))
		{
			if (len < info.width - ft_strlen(str))
				len += ft_putchar(' ');
				// len += (info.minus ? ft_putchar(*(str + len)) : ft_putchar(' '));
			else
				len += ft_putchar(*(str + len));
				// len += (info.minus ? ft_putchar(' ') : ft_putchar(*(str + len)));
		}
		return (len);
	}
	else
	{
		if (info.minus)
			len += write(1, str, ft_strlen(str));
		while (len < (info.minus ? info.width : info.width - ft_strlen(str)))
			len += ft_putchar(' ');
		if (!info.minus)
			len += write(1, str, ft_strlen(str));
		return (len);
	}
}

int		ft_putper(t_info info)
{
	int	len;
	int	c;

	c = (info.zero ? '0' : ' ');
	len = 0;
	if (info.minus)
		len += ft_putchar('%');
	while (len < info.width - 1)
		len += ft_putchar(c);
	return (len += (info.minus ? ft_putchar(' '): ft_putchar('%')));
}


int		ft_putunbr(unsigned int n)
{
	int len;

	len = 0;
	if (n >= 10)
		len += ft_putunbr(n / 10);
	len += ft_putchar(n % 10 + '0');
	return (len);
}

int		ft_puthex(unsigned int n, char s)
{
	int		len;

	len = 0;
	if (n >= 16)
		len += ft_puthex(n / 16, s);
	if (n % 16 < 10)
		len += ft_putchar(n % 16 + '0');
	else
		len += ft_putchar(n % 16 - 10 + s);
	return (len);
}

int		ft_puthex_addr(uintptr_t n)
{
	int len;

	len = 0;
	if (n >= 16)
		len += ft_puthex_addr(n / 16);
	if (n % 16 < 10)
		len += ft_putchar(n % 16 + '0');
	else
		len += ft_putchar(n % 16 - 10 + 'a');
	return (len);
}

int		ft_putaddr(void *ptr)
{
	uintptr_t addr;

	write(1, "0x", 2);
	if (!ptr)
		return (ft_putchar('0'));
	addr = (uintptr_t)ptr;
	return ft_puthex_addr(addr);
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
		len += ft_putaddr(va_arg(it, void *));
	else if (info.type == 'd' || info.type == 'i')
		len += ft_putint_info(va_arg(it, int), info);
	else if (info.type == 'u')
		len += ft_putunbr(va_arg(it, unsigned int));
	else if (info.type == 'x')
		len += ft_puthex(va_arg(it, unsigned int), 'a');
	else if (info.type == 'X')
		len += ft_puthex(va_arg(it, unsigned int), 'A');
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
