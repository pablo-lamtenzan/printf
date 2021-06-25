# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/17 18:37:40 by plamtenz     #+#   ##    ##    #+#        #
#    Updated: 2019/11/29 12:05:19 by plamtenz    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SRCS =			ft_printf.c 					\
				pf_parsing.c					\
				pf_alpha_display.c	\
				pf_aux.c				\
				libft.c						\
				pf_buffer.c \
				pf_display_digit.c \
				pf_padding.c \
				pf_itoa_octal.c\
				pf_put_numbers.c

CC =			gcc

FLAGS =			-Wall -Wextra -Werror

NAME =			libftprintf.a

AR =			ar rc

OBJS =			${SRCS:.c=.o}

${NAME} : ${OBJS}
	${AR} ${NAME} ${OBJS}

%.o:			%.c ft_printf.h
	${CC} ${FLAGS} -o $@ -c $<

all :			${NAME}

clean :
	rm -f ${OBJS}

fclean :		clean
	rm -f ${NAME}

re :			fclean all

.PHONY:			all bonus clean fclean re
