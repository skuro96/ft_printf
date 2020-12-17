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
	bool	zero;
	bool	minus;
	int		width;
	bool	dot;
	int 	precision;
	char	type;
}				t_info;

int				ft_printf(const char *, ...);
void			set_info(const char **ptr, t_info *info, va_list it);
int				digits(unsigned int nbr);
int				ft_atoi(const char *str);
int				ft_putchar(char c);
int				ft_strlen(const char *str);
char			*ft_strdup(const char *src);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_putchar_info(char c, t_info info);
int				ft_putint_info(int n, t_info info);
int				ft_putstr(char *str);
int		my_pow(int n, int pow);
int		ft_putuint_info(unsigned int n, t_info info);
int		ft_puthex_info(unsigned int n, char a_size, t_info info);
int		digits_base(unsigned int n, unsigned int base);

#endif