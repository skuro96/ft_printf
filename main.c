//#include "ft_printf.h"
#include <stdio.h>
int ft_printf(const char *format, ...);
// Total   OK: 408  KO: 623

int main(void)
{
	int ret, ft_ret;

	ret = printf("[%-05%]\n");
	ft_ret = ft_printf("[%-05%]\n");
	
	printf("%d, %d\n", ret, ft_ret);
	return (0);
}
