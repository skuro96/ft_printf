#include "ft_printf.h"

bool	is_flag(char c)
{
	return (c == '-' || c == '0');
}

void set_flag(const char **ptr, t_info *info)
{
	info->zero = false;
	info->minus = false;
	while (is_flag(**ptr))
	{
		if (**ptr == '-')
		{
			info->minus = true;
			info->zero = false;
		}
		if (**ptr == '0' && !info->minus)
			info->zero = true;
		(*ptr)++;
	}
}

bool	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

void	set_width(const char **ptr, t_info *info, va_list ap)
{
	int tmp;

	if (**ptr == '*')
	{
		tmp = va_arg(ap, int);
		if (tmp < 0)
		{
			if (!info->minus)
			{
				info->minus = true;
				info->zero = false;
			}
			info->width = -tmp;
		}
		else
			info->width = tmp;
		(*ptr)++;
	}
	else if (is_digit(**ptr))
	{
		info->width = ft_atoi(*ptr);
		while (is_digit(**ptr))
			(*ptr)++;
	}
	else
		info->width = -1;
}

void	set_precision(const char **ptr, t_info *info, va_list ap)
{
	int tmp;

	if (**ptr == '.')
	{
		info->dot = true;
		(*ptr)++;
		if (**ptr == '*')
		{
			tmp = va_arg(ap, int);
			if (tmp < 0)
			{
				info->dot = false;
				info->precision = 0;
			}
			else
				info->precision = tmp;
			(*ptr)++;
		}
		else if ('0' <= **ptr && **ptr <= '9')
		{
			info->precision = ft_atoi(*ptr);
			while ('0' <= **ptr && **ptr <= '9')
				(*ptr)++;
		}
		else
			info->precision = 0;
	}
	else
		info->dot = false;
}

void	set_specifier(const char **ptr, t_info *info)
{
	info->specifier = **ptr;
}

bool	is_specifier(char c)
{
	int i;

	i = 0;
	while ("%cspdiuxX"[i] != '\0')
	{
		if ("%cspdiuxX"[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	check_format(const char *str)
{
	while (is_flag(*str))
		str++;
	if (*str == '*')
		str++;
	else
	{
		while (is_digit(*str))
			str++;
	}
	if (*str == '.')
	{
		str++;
		if (*str == '*')
			str++;
		else
		{
			while (is_digit(*str))
				str++;
		}
	}
	return (is_specifier(*str));
}

bool	set_info(const char **ptr, t_info *info, va_list ap)
{
	(*ptr)++;
	if (!check_format(*ptr))
		return (false);
	set_flag(ptr, info);
	set_width(ptr, info, ap);
	set_precision(ptr, info, ap);
	set_specifier(ptr, info);
	return (true);
}