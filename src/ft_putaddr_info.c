#include "ft_printf.h"

int		len_addr(uintptr_t n)
{
	int len;

	len = 3;
	while (n >= 16)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char	*ft_itoa_addr(uintptr_t n)
{
	char	*dest;
	int		len;
	int		i;

	len = len_addr(n);
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
	dest[i] = '\0';
	return (dest);
}

int		ft_putaddr_info(void *ptr, t_info info)
{
	char	*num_str;
	int		dig;
	int		len;

	if (!(num_str = ft_itoa_addr((uintptr_t)ptr)))
		return (0);
	dig = ft_strlen(num_str);
	len = 0;
	if (info.width >= 0)
	{
		if (info.minus)
			len += ft_putstr(num_str);
		while (len < (info.minus ? info.width : info.width - dig))
			len += ft_putchar(' ');
		if (!info.minus)
			len += ft_putstr(num_str);
	}
	else
		len += ft_putstr(num_str);
	return (len);
}