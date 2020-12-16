#include "ft_printf.h"

char	*format_num(int n, t_info info)
{
	char *tmp;
	char *zeros;
	char *ret;
	int size;

	if (info.dot && info.precision == 0)	
		return (ft_strdup(""));
	if (!info.dot || info.precision < (n < 0 ? digits(-n) : digits(n)))
		return (ft_itoa(n));
	size = (n < 0 ? info.precision - digits(-n) + 1 : info.precision - digits(n)); 
	zeros = malloc(size + 1);
	int i = 0;
	while (i < size)
	{
		if (i == 0 && n < 0)
			zeros[i] = '-';
		else
			zeros[i] = '0';
		i++;
	}
	zeros[i] = '\0';
	tmp = (n < 0 ? ft_itoa(-n) : ft_itoa(n)); // overflow?
	ret = ft_strjoin(zeros, tmp);
	free(zeros);
	free(tmp);
	return (ret);
}

int		ft_putint_info(int n, t_info info)
{
	int len;
	int digit;
	char *num_str;

	len = 0;
	num_str = format_num(n, info); // free;
	digit = ft_strlen(num_str);
	if (info.width >= 0)
	{
		if (info.zero && !info.dot)
		{
			len += (n < 0 ? ft_putchar(*num_str++) : 0);
			while (len < info.width - digit + (n < 0 ? 1 : 0))
				len += ft_putchar('0');
			len += ft_putstr(num_str);
		}
		else
		{
			if (info.minus)
				ft_putstr(num_str);
			while (len < info.width - digit)
			{
				len += ft_putchar(' ');
			}
			if (info.minus)
				len += ft_strlen(num_str);
			else
				len += ft_putstr(num_str);
		}
	}
	else
	{
		len += ft_putstr(num_str);
	}
	return (len);
}
