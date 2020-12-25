/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skurosu <skurosu@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:58:11 by skurosu           #+#    #+#             */
/*   Updated: 2020/12/26 01:58:13 by skurosu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_flag(const char **ptr, t_info *info)
{
	while (**ptr == '-' || **ptr == '0')
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
	else if ('0' <= **ptr && **ptr <= '9')
	{
		info->width = ft_atoi(*ptr);
		while ('0' <= **ptr && **ptr <= '9')
			(*ptr)++;
	}
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
			if ((tmp = va_arg(ap, int)) < 0)
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
	}
}

bool	check_format(const char *str)
{
	while (*str == '-' || *str == '0')
		str++;
	if (*str == '*')
		str++;
	else
	{
		while ('0' <= *str && *str <= '9')
			str++;
	}
	if (*str == '.')
	{
		str++;
		if (*str == '*')
			str++;
		else
		{
			while ('0' <= *str && *str <= '9')
				str++;
		}
	}
	return (ft_strchr_tf("%cspdiuxX", *str));
}

bool	set_info(const char **ptr, t_info *info, va_list ap)
{
	(*ptr)++;
	if (!check_format(*ptr))
		return (false);
	info->zero = false;
	info->minus = false;
	info->width = -1;
	info->dot = false;
	info->precision = 0;
	info->specifier = 0;
	set_flag(ptr, info);
	set_width(ptr, info, ap);
	set_precision(ptr, info, ap);
	info->specifier = **ptr;
	return (true);
}
