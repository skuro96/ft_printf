#include "ft_printf.h"

// Total     OK: 392  KO: 639

int main(void)
{
	int ret, ft_ret;

	ret = printf("hello, %s.", "gavin");
	ft_ret = ft_printf("hello, %s.", "gavin");
	
	printf("%d, %d\n", ret, ft_ret);
	return (0);
}