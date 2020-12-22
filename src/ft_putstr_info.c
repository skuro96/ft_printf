#include "ft_printf.h"

char	*format_str(char *str, t_info info)
{
	if (!str)
		return (info.dot ? ft_strndup("(null)", info.precision) : ft_strdup("(null)"));
	else if (info.precision < 0)
		return (ft_strdup(str));
	else
		return (info.dot ? ft_strndup(str, info.precision) : ft_strdup(str));
}

int		ft_putstr_info(char *src, t_info info)
{
	char *str;
	int len;

	if (!(str = format_str(src, info)))
		return (0);
	len = 0;
	if (info.width >= 0)
	{
		len += (info.minus ? ft_putstr(str) : 0);
		while (len < (info.minus ? info.width : info.width - ft_strlen(str)))
		{
			len += (info.zero ? ft_putchar('0') : ft_putchar(' '));
		}
		len += (info.minus ? 0 : ft_putstr(str));
	}
	else
		len += ft_putstr(str);
	return (len);
}