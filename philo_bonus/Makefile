# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 13:33:53 by gasselin          #+#    #+#              #
#    Updated: 2021/10/07 14:14:56 by gasselin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus

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