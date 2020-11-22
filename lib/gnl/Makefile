NAME = gnl.a

SRC = get_next_line.c

HEAD = get_next_line.h

OBS = ${SRC:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

$(NAME): ${OBS}
	ar -rc gnl.a ${OBS}

${OBS}: ${SRC}
	${CC} -D BUFFER_SIZE=1000 -c ${FLAGS} ${SRC}

clean:
	rm -f ${OBS}

fclean: clean
	rm -f ${NAME}
	
re: fclean all
