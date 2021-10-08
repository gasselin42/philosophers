# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 10:08:19 by gasselin          #+#    #+#              #
#    Updated: 2021/10/08 12:28:37 by gasselin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= main.c \
			routine.c \
			ft_init.c \
			ft_utils.c

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf
CC		= gcc
CFLAGS	= -pthread -Wall -Wextra -Werror -g

all : ${NAME}

${NAME} : ${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean :
		${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : fclean all