#ifndef FT_PRINTF
# define FT_PRINTF

# include <stdio.h>
# include <stdlib.h> // malloc, free
# include <unistd.h> // write
# include <stdarg.h> // va_start, va_arg, va_copy, va_end
# include <stdbool.h> //bool
# include <limits.h>

typedef struct	s_info
{
	char	flag[2];
	int		width;
	bool	dot;
	int 	precision;
	char	type;
}				t_info;

int		ft_printf(const char *, ...);

#endif