#include "ft_printf.h"

// void	set_flag(const char **ptr, t_info *info)
// {
// 	if (**ptr == '0')
// 	{
// 		info->flag[0] = *(*ptr)++;
// 		if (**ptr == '-')
// 			info->flag[1] = *(*ptr)++;
// 		else
// 			info->flag[1] = 0;
// 	}
// 	else if (**ptr == '-')
// 	{
// 		info->flag[0] = *(*ptr)++;
// 		if (**ptr == '0')
// 			info->flag[1] = *(*ptr)++;
// 		else
// 			info->flag[1] = 0;
// 	}
// 	else
// 	{
// 		info->flag[0] = 0;
// 		info->flag[1] = 0;
// 	}
// }

void	set_flag(const char **ptr, t_info *info)
{
	info->zero = false;
	info->minus = false;
	if (**ptr == '0')
	{
		(*ptr)++;
		info->zero = true;
		if (**ptr == '-')
		{
			(*ptr)++;
			info->minus = true;
		}
	}
	else if (**ptr == '-')
	{
		(*ptr)++;
		info->minus = true;
		if (**ptr == '0')
		{
			(*ptr)++;
			info->zero = true;
		}
	}
}

void	set_width(const char **ptr, t_info *info, va_list ap)
{
	int dig;
	int tmp;

	if (**ptr == '*')
	{
		tmp = va_arg(ap, int);
		if (tmp < 0)
		{
			info->minus = true;
			info->width = -tmp;
		}
		else
			info->width = tmp;
		(*ptr)++;
	}
	else if ('0' <= **ptr && **ptr <= '9')
	{
		info->width = ft_atoi(*ptr);
		dig = digits(info->width);
		*ptr += dig;
	}
	else
		info->width = -1;
}

void	set_precision(const char **ptr, t_info *info, va_list ap)
{
	// int tmp;

	if (**ptr == '.')
	{
		info->dot = true;
		(*ptr)++;
		if (**ptr == '*')
		{
			// tmp = va_arg(ap, int);
			// info->precision = (tmp < 0 ? 0 : tmp);
			info->precision = va_arg(ap, int);
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