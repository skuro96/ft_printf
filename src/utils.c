#include "ft_printf.h"

int		ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int		ft_putstr(char *str)
{
	return write(1, str, ft_strlen(str));
}

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if ((dest = malloc(sizeof(char) * (ft_strlen(src) + 1))) == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	ans;

	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	ans = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - '0';
		i++;
	}
	return ((int)(ans * sign));
}

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

int		my_pow(int n, int pow)
{
	if (pow == 0)
		return (1);
	return (n * my_pow(n, pow - 1));
}

char	*ft_itoa(int n)
{
	size_t			i;
	size_t			len;
	unsigned int	nbr;
	char			*dest;

	nbr = (n < 0 ? -n : n);
	len = digits(nbr) + (n < 0 ? 1 : 0);
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (n < 0)
	{
		dest[i] = '-';
		i++;
		len--;
	}
	while (len > 0)
	{
		dest[i++] = nbr / my_pow(10, len - 1) + '0';
		nbr %= my_pow(10, len - 1);
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	if (!(dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
