//#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int ft_printf(const char *format, ...);

int main(void)
{
	int ret, ft_ret;

	int a = 42;

	// ret = printf("%*c, %*c", INT_MAX - 1, 'a', INT_MAX - 1, 'a');
	// ft_ret = ft_printf("%*c", INT_MAX - 1, 'a');

	// ret = printf("%.5,%da\n", 1);
	// ft_ret = ft_printf("%.5,%db\n", 1);

	ret = printf("[%.12d]\n", INT_MIN);
	ft_ret = ft_printf("[%.12d]\n", INT_MIN);

	printf("%d, %d\n", ret, ft_ret);
	return (0);
}
