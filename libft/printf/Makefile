# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/27 18:39:52 by ashadrin          #+#    #+#              #
#    Updated: 2026/01/07 13:29:42 by ashadrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= printf.a

SRCS		= ft_printf.c \
				ft_printf_char.c \
				ft_printf_string.c \
				ft_printf_pointer.c \
				ft_printf_int.c \
				ft_printf_hex.c

OBJS		= $(SRCS:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

all: $(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
