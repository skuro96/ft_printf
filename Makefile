NAME = libftprintf.a

CC = gcc
INCLUDE = -I ./include/

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)
RM = rm -rf

SRCDIR = ./src/
SRCNAME = 
SRCNAME += ft_printf.c
SRCNAME += set_info.c
SRCNAME += utils.c
SRCNAME += ft_putchar_info.c
SRCNAME += ft_putint_info.c

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