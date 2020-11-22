
NAME = miniRT

DEBUG = dbRT

SDIR = src

ODIR = tmp

LIBFT = lib/libft/libft.a

GNL = lib/gnl/gnl.a

LIBX = mlx_linux/libmlx.a

SRC = main.c \
service/errs/input_exceptions.c \
service/files/scene.c \
service/files/scene_handlers.c \
entities/tuple/tuple_1.c 

OBS = $(addprefix $(ODIR)/,${SRC:.c=.o})

SRCS = $(addprefix $(SDIR)/,${SRC})

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

$(DEBUG): pre-build get-gnl get-libft #get-libx
	clang -ggdb3 ${FLAGS} -o ${DEBUG} ${SRCS} ${GNL} ${LIBFT} ${LIBX} -Imlx_linux -lXext -lX11 -lm -lz

$(NAME): pre-build get-gnl get-libft  ${OBS}
	gcc ${FLAGS} -o ${NAME} ${OBS} ${GNL} ${LIBFT} ${LIBX} -Imlx_linux -lXext -lX11 -lm -lz

${ODIR}/%.o: ${SDIR}/%.c
	${CC} ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

get-gnl:
	make -C lib/gnl all clean

get-libft:
	make -C lib/libft all clean

# get-libx:
# 	./mlx_linux/configure

pre-build:
	mkdir -p ${ODIR}/service/errs
	mkdir -p ${ODIR}/service/files

clean:
	rm -rf ${ODIR}
	make -C lib/libft fclean
	make -C lib/gnl fclean
	rm -rf ${LIBX}

fclean: clean
	rm -rf ${NAME}
	rm -rf ${DEBUG}

bonus:
	all

debug: ${DEBUG}

re: fclean all

.PHONY: ${NAME} $(DEBUG)