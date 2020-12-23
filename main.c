//#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int ft_printf(const char *format, ...);

int main(void)
{
	int ret, ft_ret;

	int a = 42;

	ret = printf("%*c, %*c", INT_MAX - 1, 'a', INT_MAX - 1, 'a');
	// ft_ret = ft_printf("%*c", INT_MAX - 1, 'a');

	// printf("%d, %d\n", ret, ft_ret);
	printf("%d\n", ret);
	return (0);
}
