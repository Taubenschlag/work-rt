# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 17:35:27 by rokupin           #+#    #+#              #
#    Updated: 2023/09/22 09:27:26 by sbocanci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = \
	ft_atod.c \
	ft_atoi.c \
	ft_isdouble.c \
	ft_isnumber.c\
	ft_itoa.c \
	ft_split.c \
	ft_strcat.c \
	ft_strdup.c \
	ft_strequals.c \
	ft_strlen.c \
	ft_whitespaces.c \
	find_first.c \
	get_next_line.c

HEAD = libft.h

OBS = ${SRC:.c=.o}

CC = cc

FLAGS = -Wall -Wextra -Werror -g

all: ${NAME}
	@ranlib ${NAME}
	@#printf "\e[0;36m>>> ${NAME} ready\n\e[0m"

$(NAME): ${OBS}
	ar -rcs ${NAME} ${OBS} 
	@#printf "\e[0;36mGenerated libft objects \n\e[0m" $@

${OBS}: ${SRC}
	${CC} -g -c -I ${FLAGS} ${SRC} ${BNS}
	@#printf "\e[0;36mCompiled libft\n\e[0m" $@

clean:
	rm -f ${OBS}
	rm -f libft.h.gch
	@#printf "\e[0;31mlibft objects removed\n\e[0m" $@

fclean: clean
	rm -f ${NAME}
	@#printf "\e[0;31m${NAME} removed\n\e[0m" $@
	
re: fclean all

.PHONY: all clean fclean re

.SILENT:
