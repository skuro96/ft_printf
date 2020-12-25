#include "ft_printf.h"

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

char	*ft_strndup(const char *src, int n)
{
	char	*dest;
	int		i;

	i = 0;
	if (!(dest = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_itoa(int nbr)
{
	char			*dest;
	unsigned int	n;
	int				len;
	int				i;

	n = (nbr < 0 ? -nbr : nbr);
	len = digits(n) + (nbr < 0 ? 1 : 0);
	if (!(dest = malloc(len + 1)))
		return (NULL);
	i = len - 1;
	while (i >= 0)
	{
		if (i == 0 && nbr < 0)
			dest[i] = '-';
		else
		{
			dest[i] = n % 10 + '0';
			n /= 10;
		}
		i--;
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_itoa_2(unsigned int n, bool minus)
{
	char	*dest;
	size_t	len;
	int		i;

	len = digits(n) + (minus ? 1 : 0);
	if (!(dest = malloc(len + 1)))
		return (NULL);
	i = len - 1;
	while (i >= 0)
	{
		if (i == 0 && minus)
			dest[i] = '-';
		else
		{
			dest[i] = n % 10 + '0';
			n /= 10;
		}
		i--;
	}
	dest[len] = '\0';
	return (dest);
}
