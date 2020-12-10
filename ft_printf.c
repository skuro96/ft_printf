#include "ft_printf.h"

int		ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int		ft_putchar_info(char c, t_info info)
{
	int	len;
	int	f;

	f = (info.flag[0] == '0' ? '0' : ' ');
	len = 0;
	if (info.flag[0] == '-')
		len += ft_putchar(c);
	while (len < info.width - 1)
		len += ft_putchar(f);
	if (info.flag[0] != '-')
		len += ft_putchar(c);
	return (len);
}

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if ((dest = malloc(sizeof(char) * (ft_strlen(src) + 1))) == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_putstr(char *src, t_info info)
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
				// len += (info.flag[0] == '-' ? ft_putchar(*(str + len)) : ft_putchar(' '));
			else
				len += ft_putchar(*(str + len));
				// len += (info.flag[0] == '-' ? ft_putchar(' ') : ft_putchar(*(str + len)));
		}
		return (len);
	}
	else
	{
		if (info.flag[0] == '-')
			len += write(1, str, ft_strlen(str));
		while (len < (info.flag[0] == '-' ? info.width : info.width - ft_strlen(str)))
			len += ft_putchar(' ');
		if (info.flag[0] != '-')
			len += write(1, str, ft_strlen(str));
		return (len);
	}
}

int		ft_putper(t_info info)
{
	int	len;
	int	c;

	c = (info.flag[0] == '0' ? '0' : ' ');
	len = 0;
	if (info.flag[0] == '-')
		len += ft_putchar('%');
	while (len < info.width - 1)
		len += ft_putchar(c);
	return (len += (info.flag[0] == '-' ? ft_putchar(' '): ft_putchar('%')));
}

int		ft_putnbr(int n)
{
	unsigned int	nbr;
	int				len;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = n;
	if (nbr >= 10)
		len += ft_putnbr(nbr / 10);
	len += ft_putchar(nbr % 10 + '0');
	return (len);
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

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int		digits(unsigned int nbr)
{
	int dig;

	dig = 1;
	while (nbr >= 10)
	{
		dig++;
		nbr /= 10;
	}
	return (dig);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	ans;

	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	ans = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - '0';
		if (sign < 0 && ans >= (unsigned long)(-LONG_MIN))
			return (0);
		if (sign > 0 && ans >= LONG_MAX)
			return (-1);
		i++;
	}
	return ((int)(ans * sign));
}

bool	inrange(char c, char begin, char end)
{
	return (begin <= c && c <= end);
}

void	set_flag(const char **ptr, t_info *info)
{
	if (**ptr == '0')
	{
		info->flag[0] = *(*ptr)++;
		if (**ptr == '-')
			info->flag[1] = *(*ptr)++;
	}
	else if (**ptr == '-')
	{
		info->flag[0] = *(*ptr)++;
		if (**ptr == '0')
			info->flag[1] = *(*ptr)++;
	}
}

void	set_width(const char **ptr, t_info *info, va_list it)
{
	int dig;

	if (**ptr == '*')
	{
		info->width = va_arg(it, int);
		(*ptr)++;
	}
	else if (ft_isdigit(**ptr))
	{
		info->width = ft_atoi(*ptr);
		dig = digits(info->width);
		*ptr += dig;
	}
	else
		info->width = 0;
}

void	set_precision(const char **ptr, t_info *info, va_list it)
{
	int dig;

	if (**ptr == '.')
	{
		info->dot = true;
		(*ptr)++;
		if (**ptr == '*')
		{
			info->precision = va_arg(it, int);
			(*ptr)++;
		}
		else if (ft_isdigit(**ptr))
		{
			info->precision = ft_atoi(*ptr);
			dig = digits(info->precision);
			*ptr += dig;
		}
	}
	else
		info->dot = false;
}

void	set_type(const char **ptr, t_info *info)
{
	info->type = **ptr;
}

void	set_info(const char **ptr, t_info *info, va_list it)
{
	(*ptr)++;
	set_flag(ptr, info);
	set_width(ptr, info, it);
	set_precision(ptr, info, it);
	set_type(ptr, info);
}

int		convert(const char **ptr, va_list it)
{
	int len;
	t_info info;

	len = 0;
	set_info(ptr, &info, it);
	// printf("\nflag: %s\nwidth: %d\ndot: %d\nprecision: %d\ntype=%c\n\n", info.flag, info.width, info.dot, info.precision, info.type);
	if (info.type == '%')
		len += ft_putper(info);
	else if (info.type == 'c')
		len += ft_putchar_info(va_arg(it, int), info);
	else if (info.type == 's')
		len += ft_putstr(va_arg(it, char *), info);
	else if (info.type == 'p')
		len += ft_putaddr(va_arg(it, void *));
	else if (info.type == 'd' || info.type == 'i')
		len += ft_putnbr(va_arg(it, int));
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
