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
	// printf("minus : %d, zero : %d\n", info->minus, info->zero);
}

// void	set_flag(const char **ptr, t_info *info)
// {
// 	info->zero = false;
// 	info->minus = false;
// 	if (**ptr == '0')
// 	{
// 		(*ptr)++;
// 		info->zero = true;
// 		if (**ptr == '-')
// 		{
// 			(*ptr)++;
// 			info->minus = true;
// 		}
// 	}
// 	else if (**ptr == '-')
// 	{
// 		(*ptr)++;
// 		info->minus = true;
// 		if (**ptr == '0')
// 		{
// 			(*ptr)++;
// 			info->zero = true;
// 		}
// 	}
// }

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

void	set_type(const char **ptr, t_info *info)
{
	info->type = **ptr;
}

void	set_info(const char **ptr, t_info *info, va_list ap)
{
	(*ptr)++;
	set_flag(ptr, info);
	set_width(ptr, info, ap);
	set_precision(ptr, info, ap);
	set_type(ptr, info);
}