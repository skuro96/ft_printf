NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

INCDIR = ./
INCNAME = ft_printf.h

SRCDIR = ./
SRCNAME = ft_printf.c

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