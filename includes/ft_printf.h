/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skurosu <skurosu@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 03:25:59 by skurosu           #+#    #+#             */
/*   Updated: 2020/12/26 03:26:53 by skurosu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>

typedef struct	s_info
{
	bool	zero;
	bool	minus;
	int		width;
	bool	dot;
	int		precision;
	char	spec;
}				t_info;

int				ft_printf(const char *format, ...);

bool			set_info(const char **ptr, t_info *info, va_list it);
int				ft_putchar_info(char c, t_info info);
int				ft_putstr_info(char *src, t_info info);
int				ft_putaddr_info(void *ptr, t_info info);
int				ft_putint_info(int n, t_info info);
int				ft_putuint_info(unsigned int n, t_info info);
int				ft_puthex_info(unsigned int n, char a_size, t_info info);

char			*ft_strdup(const char *src);
char			*ft_strndup(const char *src, int n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int nbr);
char			*ft_itoa_us(unsigned int n);

int				digits(unsigned int nbr);
int				digits_base(unsigned int n, unsigned int base);
int				ft_atoi(const char *str);

int				ft_putchar(char c);
int				ft_putstr(char *str);
int				ft_strlen(const char *str);
bool			ft_strchr_tf(char *str, char c);
char			*freeturn(char **s1, char **s2, char *ret);

#endif
