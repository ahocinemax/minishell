# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 12:12:29 by mtsuji            #+#    #+#              #
#    Updated: 2022/08/21 22:09:19 by mtsuji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_malloc.c						\
			ft_memset.c						\
			ft_bzero.c						\
			ft_memcpy.c						\
			ft_memccpy.c					\
			ft_memmove.c					\
			ft_memchr.c						\
			ft_memcmp.c						\
			ft_strlen.c						\
			ft_isalpha.c					\
			ft_isdigit.c					\
			ft_isalnum.c					\
			ft_isascii.c					\
			ft_isprint.c					\
			ft_isspace.c					\
			ft_toupper.c					\
			ft_tolower.c					\
			ft_strchr.c						\
			ft_strrchr.c					\
			ft_strncmp.c					\
			ft_strcmp.c						\
			ft_strlcpy.c					\
			ft_strlcat.c					\
			ft_strnstr.c					\
			ft_atoi.c						\
			ft_calloc.c						\
			ft_strdup.c						\
			ft_substr.c						\
			ft_strjoin.c					\
			ft_strtrim.c					\
			ft_split.c						\
			ft_itoa.c						\
			ft_strmapi.c					\
			ft_putchar_fd.c					\
			ft_putstr_fd.c					\
			ft_putendl_fd.c					\
			ft_putnbr_fd.c					\
			ft_strncpy.c 					\
			ft_strcpy.c 					\
			ft_printf/outil_ft_printf.c		\
			ft_printf/outil2.c				\
			ft_printf/print_before_sign.c	\
			ft_printf/conversion_checker.c	\
			ft_printf/ft_printf.c			\
			ft_lstnew.c						\
			ft_lstadd_front.c				\
			ft_lstsize.c					\
			ft_lstlast.c					\
			ft_lstadd_back.c				\
			ft_lstdelone.c					\
			ft_lstclear.c					\
			ft_lstiter.c					\
			ft_lstmap.c

OBJS	=	${SRCS:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

NAME	=	libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		ar rcs ${NAME} ${OBJS}
		ranlib ${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}
fclean:		clean
		${RM} ${NAME}
re:	fclean all

.PHONY:	all clean fclean re
