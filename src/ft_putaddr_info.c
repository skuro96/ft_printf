#include "ft_printf.h"

int		len_addr(uintptr_t n, t_info info)
{
	int len;

	len = 1;
	while (n >= 16)
	{
		n /= 16;
		len++;
	}
	if (info.dot)
		len = (info.precision > len ? info.precision : len);
	return (len + 2);
}

char	*ft_itoa_addr(uintptr_t n, t_info info)
{
	char	*dest;
	int		len;
	int		i;

	len = len_addr(n, info);
	if (!(dest = malloc(len + 1)))
		return (NULL);
	i = len - 1;
	while (i >= 0)
	{
		if (i == 0)
			dest[i] = '0';
		else if (i == 1)
			dest[i] = 'x';
		else
		{
			dest[i] = (n % 16 < 10 ? n % 16 + '0' : n % 16 - 10 + 'a');
			n /= 16;
		}
		i--;
	}
	dest[len] = '\0';
	return (dest);
}

int		ft_putaddr_info(void *ptr, t_info info)
{
	char	*num_str;
	int		dig;
	int		len;

	if (!ptr && info.dot && info.precision == 0)
	{
		if (!(num_str = ft_strdup("0x")))
			return (-1);
	}
	else if (!(num_str = ft_itoa_addr((uintptr_t)ptr, info)))
		return (-1);
	dig = ft_strlen(num_str);
	len = 0;
	if (info.width >= 0)
	{
		len += (info.minus ? ft_putstr(num_str) : 0);
		while (len < (info.minus ? info.width : info.width - dig))
			len += ft_putchar(' ');
		len += (info.minus ? 0 : ft_putstr(num_str));
	}
	else
		len += ft_putstr(num_str);
	free(num_str);
	return (len);
}