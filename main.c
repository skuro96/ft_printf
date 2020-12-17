//#include "ft_printf.h"
#include <stdio.h>
int ft_printf(const char *format, ...);
// Total   OK: 408  KO: 623

int main(void)
{
	int ret, ft_ret;

	int a = 42;

	ret = printf("[%p]\n", &a);
	ft_ret = ft_printf("[%p]\n", &a);
	
	printf("%d, %d\n", ret, ft_ret);
	return (0);
}
