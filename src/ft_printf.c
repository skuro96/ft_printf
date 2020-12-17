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

	c = (info.zero && !info.minus ? '0' : ' ');
	len = 0;
	if (info.minus)
		len += ft_putchar('%');
	while (len < info.width - 1)
		len += ft_putchar(c);
	return (len += (info.minus ? ft_putchar(' '): ft_putchar('%')));
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

int		len_addr(uintptr_t n)
{
	int len;

	len = 3;
	while (n >= 16)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char	*ft_itoa_addr(uintptr_t n)
{
	char	*dest;
	int		len;
	int		i;

	len = len_addr(n);
	if (!(dest = malloc(len + 1)))
		return (NULL);
	i = len - 1;
	while (i >= 0)
	{
		if (i == 0)
			dest[i] = '0';
		else if (i == 1)
			dest[i] = 'x';
		else
		{
			dest[i] = (n % 16 < 10 ? n % 16 + '0' : n % 16 - 10 + 'a');
			n /= 16;
		}
		i--;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_putaddr_info(void *ptr, t_info info)
{
	char	*num_str;
	int		dig;
	int		len;

	if (!(num_str = ft_itoa_addr((uintptr_t)ptr)))
		return (0);
	dig = ft_strlen(num_str);
	len = 0;
	if (info.width >= 0)
	{
		if (info.minus)
			len += ft_putstr(num_str);
		while (len < (info.minus ? info.width : info.width - dig))
			len += ft_putchar(' ');
		if (!info.minus)
			len += ft_putstr(num_str);
	}
	else
		len += ft_putstr(num_str);
	return (len);
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
