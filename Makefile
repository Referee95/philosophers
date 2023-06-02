# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 10:54:36 by ykhalil-          #+#    #+#              #
#    Updated: 2023/05/05 11:36:14 by ykhalil-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM = philo

SRCS = utils.c \

CC= gcc

CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

all : $(PROGRAM)

$(PROGRAM) : $(OBJS) philo.c
		$(CC) $(CFLAGS) $^ -o $(PROGRAM)
clean : 
	@rm -rf $(OBJS) 
fclean : clean
	@rm -rf $(OBJS) $(PROGRAM)
	
re : fclean all