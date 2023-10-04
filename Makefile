#/__//_//_/\  /_______/\/__/\ /__/\  /_______/\/_____/\ /________/\	#
#\::\| \| \ \ \__.::._\/\::\_\\  \ \ \__.::._\/\:::_ \ \\__.::.__\/	#
# \:.      \ \   \::\ \  \:. `-\  \ \   \::\ \  \:(_) ) )_ \::\ \	#
#  \:.\-/\  \ \  _\::\ \__\:. _    \ \  _\::\ \__\: __ `\ \ \::\ \	#
#   \. \  \  \ \/__\::\__/\\. \`-\  \ \/__\::\__/\\ \ `\ \ \ \::\ \	#
#    \__\/ \__\/\________\/ \__\/ \__\/\________\/ \_\/ \_\/  \__\/	#

NAME = miniRT

DEBUG = dbRT

SAN = sanRT

SDIR = src

ODIR = tmp

LIBFT = lib/libft/libft.a

LIBX = mlx_linux/libmlx.a

SRC = \
main.c \
general_utils.c \
\
entities/bmp/bmp.c \
\
entities/camera/camera.c \
\
entities/color/colors_get.c \
entities/color/colors_set.c \
\
entities/intersection/intersection_1.c \
entities/intersection/intersection_2a.c \
entities/intersection/intersection_2.c \
entities/intersection/intersection_3.c \
entities/intersection/intersection_4.c \
entities/intersection/intersection.c \
entities/intersection/pattern.c \
entities/intersection/world.c \
\
entities/light/light.c \
\
entities/material/material_1.c \
entities/material/material.c \
\
entities/matrix/matrix_advanced_1.c \
entities/matrix/matrix_advanced_2.c \
entities/matrix/matrix_advanced_3.c \
entities/matrix/matrix_basic.c \
entities/matrix/matrix_transformations.c \
\
entities/ray/ray.c \
\
entities/shapes/cone/cone.c \
entities/shapes/cube/cube.c \
entities/shapes/cylinder/cylinder.c \
entities/shapes/plane/plane.c \
entities/shapes/shape.c \
entities/shapes/sphere/sphere.c \
entities/shapes/square/square.c \
entities/shapes/triangle/triangle.c \
\
entities/tuple/tuple_advanced_1.c \
entities/tuple/tuple_advanced_2.c \
entities/tuple/tuple_advanced_3.c \
entities/tuple/tuple_basic.c \
\
service/errs/file_instructions_checker.c \
service/errs/file_shape_description_checker.c \
service/errs/valid_input.c \
\
service/files/scene_1.c \
service/files/scene.c \
service/files/scene_handlers.c \
service/files/scene_handlers_1.c \
service/files/scene_handlers_2.c \
service/files/scene_handlers_3.c \
\
service/window/mlx_handlers.c \
service/window/window.c \
\
service/free/free.c \
service/free/free_intersect.c


OBS = $(addprefix $(ODIR)/,${SRC:.c=.o})

SRCS = $(addprefix $(SDIR)/,${SRC})

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

$(SAN): pre-build get-libft #get-libx
	${CC} ${FLAGS} -O1 -g -fsanitize=address -o ${SAN} ${SRCS} ${LIBFT} ${LIBX} -Imlx_linux -lXext -lX11 -lm -lz

$(NAME): pre-build get-libft get-libx ${OBS}
	${CC} ${FLAGS} -o ${NAME} ${OBS} ${LIBFT} ${LIBX} -Imlx_linux -lXext -lX11 -lm -lz

${ODIR}/%.o: ${SDIR}/%.c
	${CC} ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

get-libft:
	make -C lib/libft all clean

get-libx:
	make -C mlx_linux

pre-build:
	mkdir -p ${ODIR}/service/free
	mkdir -p ${ODIR}/service/errs
	mkdir -p ${ODIR}/service/files
	mkdir -p ${ODIR}/service/window
	mkdir -p ${ODIR}/entities/tuple
	mkdir -p ${ODIR}/entities/matrix
	mkdir -p ${ODIR}/entities/ray
	mkdir -p ${ODIR}/entities/light
	mkdir -p ${ODIR}/entities/color
	mkdir -p ${ODIR}/entities/material
	mkdir -p ${ODIR}/entities/shapes/cone
	mkdir -p ${ODIR}/entities/shapes/cube
	mkdir -p ${ODIR}/entities/shapes/cylinder
	mkdir -p ${ODIR}/entities/shapes/plane
	mkdir -p ${ODIR}/entities/shapes/sphere
	mkdir -p ${ODIR}/entities/shapes/triangle
	mkdir -p ${ODIR}/entities/shapes/square
	mkdir -p ${ODIR}/entities/bmp
	mkdir -p ${ODIR}/entities/intersection
	mkdir -p ${ODIR}/entities/camera

clean:
	rm -rf ${ODIR}
	make -C lib/libft fclean
	make -C mlx_linux clean

fclean: clean
	rm -rf ${NAME}
	rm -rf ${DEBUG}
	rm -rf ${SAN}

bonus:
	all

debug: ${DEBUG}

asan: ${SAN}

re: fclean all

.PHONY: ${NAME} $(DEBUG) ${SAN}
