#include "ft_printf.h"

char	*ft_itoa_hex(unsigned int n, char a_size)
{
	char	*dest;
	int		len;
	int		i;
	int		dig;

	len = digits_base(n, 16);
	if (!(dest = malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dig = my_pow(16, len - i - 1);
		dest[i] = (n / dig < 10 ? n / dig + '0' : n / dig - 10 + a_size);
		n %= dig;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*format_hex(unsigned int n, char a_size, t_info info)
{
	int		size;
	char	*zeros;
	char	*tmp;
	char	*ret;
	int		i;

	if (info.dot && info.precision == 0)
		return (ft_strdup(""));
	if (!info.dot || info.precision < digits_base(n, 16))
		return (ft_itoa_hex(n, a_size));
	size = info.precision - digits_base(n, 16);
	if (!(zeros = malloc(size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		zeros[i] = '0';
		i++;
	}
	zeros[i] = '\0';
	if (!(tmp = ft_itoa_hex(n, a_size)))
		return (NULL); //zerosのfreeも
	ret = ft_strjoin(zeros, tmp);
	free(zeros);
	free(tmp);
	return (ret);
}

int		ft_puthex_info(unsigned int n, char a_size, t_info info)
{
	char	*num_str;
	int		dig;
	int		len;

	if (!(num_str = format_hex(n, a_size, info)))
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
			len += ft_putstr(num_str);
		while (len < (info.minus ? info.width : info.width - dig))
			len += ft_putchar(' ');
		if (!info.minus)
			len += ft_putstr(num_str);
		}
	}
	else
		len += ft_putstr(num_str);
	return (len);	
}