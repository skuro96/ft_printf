#include "ft_printf.h"

char	*ft_itoa_uint(unsigned int n)
{
	char *dest;
	int len;
	int i;
	int dig;

	len = digits(n);
	if (!(dest = malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dig = my_pow(10, len - i - 1);
		dest[i] = n / dig + '0';
		n %= dig;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*format_uint(unsigned int n, t_info info)
{
	char *tmp;
	char *zeros;
	char *ret;
	int size;
	int i;

	if (info.dot && info.precision == 0)
		return (ft_strdup(""));
	if (!info.dot || info.precision < digits(n))
		return (ft_itoa_uint(n));
	size = info.precision - digits(n);
	if (!(zeros = malloc(size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		zeros[i] = '0';
		i++;
	}
	zeros[i] = '\0';
	if (!(tmp = ft_itoa_uint(n)))
		return (NULL);
	ret = ft_strjoin(zeros, tmp); //free
	free(zeros);
	free(tmp);
	return (ret);
}

int		ft_putuint_info(unsigned int n, t_info info)
{
	char *num_str;
	int dig;
	int len;

	if (!(num_str = format_uint(n, info)))
		return (0);
	dig = ft_strlen(num_str);
	len = 0;
	if (info.width >= 0)
	{
		if (info.zero && !info.dot)
		{
			while (len < info.width - dig)
				len += ft_putchar('0');
			len += ft_putstr(num_str);
		}
		else
		{
			if (info.minus)
				ft_putstr(num_str);
			while (len < info.width - dig)
				len += ft_putchar(' ');
			if (info.minus)
				len += ft_strlen(num_str);
			else
				len += ft_putstr(num_str);
		}
	}
	else
		len += ft_putstr(num_str);
	free(num_str);
	return (len);
}