//#include "ft_printf.h"
#include <stdio.h>
int ft_printf(const char *format, ...);
// Total   OK: 408  KO: 623

int main(void)
{
	int ret, ft_ret;

	int a = 42;

	// ret = printf("[%05.*d]\n", -15, 42);
	// ft_ret = ft_printf("[%05.*d]\n", -15, 42);

	// ret = printf("[%0-5d]\n", 420);
	// ft_ret = ft_printf("[%0-5d]\n", 420);

	ret = printf("[%2.9p]\n", 1234);
	ft_ret = ft_printf("[%2.9p]\n", 1234);

	printf("%d, %d\n", ret, ft_ret);
	return (0);
}
