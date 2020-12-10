#include "ft_printf.h"

// Total   OK: 408  KO: 623

int main(void)
{
	int ret, ft_ret;

	ret = printf("[%-c]\n", 'a');
	ft_ret = ft_printf("[%-c]\n", 'a');

	// ret = printf("[%7.5s]\n", "yolo");
	// ft_ret = ft_printf("[%7.5s]\n", "yolo");
	
	printf("%d, %d\n", ret, ft_ret);
	return (0);
}
