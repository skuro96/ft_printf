//#include "ft_printf.h"
#include <stdio.h>
int ft_printf(const char *format, ...);
// Total   OK: 408  KO: 623

int main(void)
{
	int ret, ft_ret;

	ret = printf("[%-s]\n", "hello");
	ft_ret = ft_printf("[%-s]\n", "hello");
	
	printf("%d, %d\n", ret, ft_ret);
	return (0);
}
