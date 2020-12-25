#include "ft_printf.h"

int		digits(unsigned int nbr)
{
	int dig;

	dig = 1;
	while (nbr >= 10)
	{
		dig++;
		nbr /= 10;
	}
	return (dig);
}

int		digits_base(unsigned int n, unsigned int base)
{
	int dig;

	dig = 1;
	while (n >= base)
	{
		dig++;
		n /= base;
	}
	return (dig);
}

int		ft_atoi(const char *str)
{
	int				i;
	unsigned long	ans;

	i = 0;
	ans = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - '0';
		i++;
	}
	return ((int)ans);
}
