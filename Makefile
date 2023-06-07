# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 10:54:36 by ykhalil-          #+#    #+#              #
#    Updated: 2023/06/07 19:28:51 by ykhalil-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM = philo

SRCS = routine.c utils.c utils2.c \

CC= gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

OBJS = ${SRCS:.c=.o}

all : $(PROGRAM)

$(PROGRAM) : $(OBJS) philo.c
		$(CC) $(CFLAGS) $^ -o $(PROGRAM)
clean : 
	@rm -rf $(OBJS) 
fclean : clean
	@rm -rf $(OBJS) $(PROGRAM)
	
re : fclean all