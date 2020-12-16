#include "ft_printf.h"

int		ft_putchar_info(char c, t_info info)
{
	int	len;
	int	ch;

	ch = (info.zero ? '0' : ' ');
	len = 0;
	if (info.minus)
		len += ft_putchar(c);
	while (len < info.width - 1)
		len += ft_putchar(ch);
	if (!info.minus)
		len += ft_putchar(c);
	return (len);
}