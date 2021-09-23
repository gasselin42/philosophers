# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 10:08:19 by gasselin          #+#    #+#              #
#    Updated: 2021/09/09 11:48:24 by gasselin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= main.c \
			routine.c \
			ft_utils.c

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf
CC		= gcc
FLAGS	= -pthread -Wall -Wextra -Werror -g

all : ${OBJS}
		${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean :
		${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : fclean all