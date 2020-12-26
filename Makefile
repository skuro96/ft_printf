NAME = libftprintf.a

CC = gcc
INCLUDE = -I ./includes/

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)
RM = rm -rf

SRCDIR = ./srcs/

SRCNAME = 
SRCNAME += ft_printf.c
SRCNAME += set_info.c
SRCNAME += ft_putchar_info.c
SRCNAME += ft_putstr_info.c
SRCNAME += ft_putaddr_info.c
SRCNAME += ft_putint_info.c
SRCNAME += ft_putuint_info.c
SRCNAME += ft_puthex_info.c
SRCNAME += utils_mal.c
SRCNAME += utils_num.c
SRCNAME += utils_str.c

SRCS = $(addprefix $(SRCDIR),$(SRCNAME))
OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)

all:		$(NAME)

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
