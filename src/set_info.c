#include "ft_printf.h"

void	set_flag(const char **ptr, t_info *info)
{
	if (**ptr == '0')
	{
		info->flag[0] = *(*ptr)++;
		if (**ptr == '-')
			info->flag[1] = *(*ptr)++;
		else
			info->flag[1] = 0;
	}
	else if (**ptr == '-')
	{
		info->flag[0] = *(*ptr)++;
		if (**ptr == '0')
			info->flag[1] = *(*ptr)++;
		else
			info->flag[1] = 0;
	}
	else
	{
		info->flag[0] = 0;
		info->flag[1] = 0;
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
	else if ('0' <= **ptr && **ptr <= '9')
	{
		info->width = ft_atoi(*ptr);
		dig = digits(info->width);
		*ptr += dig;
	}
	else
		info->width = -1;
}

void	set_precision(const char **ptr, t_info *info, va_list it)
{
	if (**ptr == '.')
	{
		info->dot = true;
		(*ptr)++;
		if (**ptr == '*')
		{
			info->precision = va_arg(it, int);
			(*ptr)++;
		}
		else if ('0' <= **ptr && **ptr <= '9')
		{
			info->precision = ft_atoi(*ptr);
			*ptr += digits(info->precision);
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