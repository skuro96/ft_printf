#include "ft_printf.h"

typedef struct	s_info
{
	char	flag[2];
	int		width;
	bool	dot;
	int 	precision;
	char	type;
}				t_info;

int		putcharl(char c)
{
	return (write(1, &c, 1));
}

bool	inrange(char c, char begin, char end)
{
	return (begin <= c && c <= end);
}

void	set_flag(char **ptr, t_info *info)
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

void	set_width(char **ptr, t_info *info)
{
	int dig;

	if (**ptr == '*')
	{
		info->width = -1;
		*ptr++;
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

void	set_precision(char **ptr, t_info *info)
{
	int dig;

	if (**ptr == '.')
	{
		info->dot = true;
		(*ptr)++;
		if (**ptr == '*')
		{
			info->precision = -1;
			(*ptr)++;
		}
		else if (ft_isdigit(**ptr))
		{
			info->precision = ft_atoi(*ptr);
			dig = digits(info->precision);
			*ptr += dig;
		}
	}
}

void	set_type(char **ptr, t_info *info)
{
	info->type = **ptr;
}

void	set_info(char **ptr, t_info *info)
{
	(*ptr)++;
	set_flag(ptr, info);
	set_width(ptr, info);
	set_precision(ptr, info);
	set_type(ptr, info);
}

int		convert(const char **ptr, va_list it)
{
	int len;
	t_info info;

	len = 0;
	set_info(ptr, &info);
	if (info.type == 'c')
		len += putcharl(va_arg(it, int), info);
	// else if (**ptr == 'd' || **ptr == 'i')
	// 	len += putintl(va_arg(it, int));
	if (**ptr == 's')
		//mojiretsuwosyutsuryokuda!!!!
	return (len);
}

int		ft_printf(const char *format, ...)
{
	int n;
	int len;
	va_list it;

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