# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 13:33:53 by gasselin          #+#    #+#              #
#    Updated: 2021/09/22 13:41:34 by gasselin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus

CC		= gcc
FLAGS	= -Wall -Wextra -Werror -g
RM		= rm -rf

SRCS	= main.c \
			routine.c \
			ft_utils.c

OBJS	= ${SRCS:.c=.o}

all :	${OBJS}
		${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean :
		${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : fclean all