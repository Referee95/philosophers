# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 10:54:36 by ykhalil-          #+#    #+#              #
#    Updated: 2023/06/08 12:52:02 by ykhalil-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = routine.c utils.c utils2.c \

CC= cc

CFLAGS = -Wall -Wextra -Werror 

OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS) philo.c
		$(CC) $(CFLAGS) $^ -o $(NAME)
clean : 
	@rm -rf $(OBJS) 
fclean : clean
	@rm -rf $(OBJS) $(NAME)
	
re : fclean all