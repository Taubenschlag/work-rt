#/__//_//_/\  /_______/\/__/\ /__/\  /_______/\/_____/\ /________/\	#
#\::\| \| \ \ \__.::._\/\::\_\\  \ \ \__.::._\/\:::_ \ \\__.::.__\/	#
# \:.      \ \   \::\ \  \:. `-\  \ \   \::\ \  \:(_) ) )_ \::\ \	#
#  \:.\-/\  \ \  _\::\ \__\:. _    \ \  _\::\ \__\: __ `\ \ \::\ \	#
#   \. \  \  \ \/__\::\__/\\. \`-\  \ \/__\::\__/\\ \ `\ \ \ \::\ \	#
#    \__\/ \__\/\________\/ \__\/ \__\/\________\/ \_\/ \_\/  \__\/	#

NAME = miniRT

_NC=`tput sgr0`
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;95m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

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
service/errs/file_check_handler.c \
service/errs/file_instructions_checker.c \
service/errs/file_shape_description_checker.c \
service/errs/input_exceptions.c \
\
service/files/scene_1.c \
service/files/scene.c \
service/files/scene_handlers_1.c \
service/files/scene_handlers_2.c \
service/files/scene_handlers.c \
\
service/window/mlx_handlers.c \
service/window/window.c

OBS = $(addprefix $(ODIR)/,${SRC:.c=.o})

SRCS = $(addprefix $(SDIR)/,${SRC})

CC = cc

FLAGS = -Wall -Wextra -Werror

all: ${NAME}
	@printf "\e[92;5;118m\n>>> miniRT ready\n\e[0m"

$(SAN): pre-build get-libft #get-libx
	${CC} ${FLAGS} -O1 -g -fsanitize=address -o ${SAN} ${SRCS} ${LIBFT} ${LIBX} -Imlx_linux -lXext -lX11 -lm -lz

$(DEBUG): pre-build get-libft #get-libx
	${CC} ${FLAGS} -ggdb3  -o ${DEBUG} ${SRCS} ${LIBFT} ${LIBX} -Imlx_linux -lXext -lX11 -lm -lz

$(NAME): pre-build get-libft  ${OBS}
	${CC} ${FLAGS} -o ${NAME} ${OBS} ${LIBFT} ${LIBX} -Imlx_linux -lXext -lX11 -lm -lz

${ODIR}/%.o: ${SDIR}/%.c
	${CC} ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@
	@printf "$(_CYAN)Generating miniRT objects in ...$(_BLUE)%-33.33s\r$(_NC)" $@

get-libft:
	make -C lib/libft all clean
#	@printf "$(_CYAN)Generating $(LIBFT) Libft...$(_BLUE)%-33.33s\r$(_NC)" $@

# get-libx:
# 	./mlx_linux/configure

pre-build:
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
	@printf "\033[00;31m>>> objects removed.\n\033[00m"
# 	rm -rf ${LIBX} 

fclean: clean
	rm -rf ${NAME}
	rm -rf ${DEBUG}
	rm -rf ${SAN}
	@printf "\033[00;31m>>> executable removed.\n\033[00m"

bonus:
	all

debug: ${DEBUG}

asan: ${SAN}

re: fclean all

.PHONY: ${NAME} $(DEBUG) ${SAN}

.SILENT:
