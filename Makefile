# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 11:10:51 by jtrancos          #+#    #+#              #
#    Updated: 2021/02/02 17:56:04 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	cub3d.c\
				./parser/parse_file.c\
				./parser/parse_texture.c\
				./parser/parse_resolution.c\
				./parser/parse_colour.c\
				./parser/parse_map.c\
				./parser/parser_utils.c\
				./parser/parser_misc.c\
				./utils/GNL/get_next_line.c\
				./raycasting/raycasting.c\
				./raycasting/draw_texture.c\
				./raycasting/raycasting_utils.c\
				./raycasting/draw_sprites.c\
				./raycasting/sky_wall_floor.c\
				./movement/movement.c\
				./movement/rotation.c\
				./events/events.c\
				./utils/handle_errors/handle_error.c\
				./utils/handle_errors/colour_error.c\
				./utils/handle_errors/player_error.c\
				./utils/handle_errors/file_error.c\
				./utils/handle_errors/map_error.c\
				./utils/handle_errors/res_error.c\
				./utils/handle_errors/tex_error.c\
				./utils/utils.c\
				./screenshot/create_bmp.c\


OBJS		= ${SRCS:.c=.o}
NAME		= cub3D
CC			= gcc
RM			= rm -f
#CFLAGS		= -Werror -Wall -Wextra
FRAMEWORK	= -lz -L . -lmlx -lft -framework AppKit -framework OpenGL 
# MINILIB APPLE -lz -L . -lmlx -framework AppKit -framework OpenGL 
# MINILIB LINUX -lmlx -lm -lbsd -lXext -lX11
# AT HOME -L . -lft -lm
LIBS		= -Lmlx_linux



.c.o:
			${CC} -g -c $< -o ${<:.c=.o}
			#gcc -o $@ -c $< $(CFLAGS)

${NAME}:	${OBJS}
			${MAKE} -C ./mlx
			#${MAKE} -C ./mlx_linux
			${MAKE} -C ./libft
			mv ./mlx/libmlx.a .
			mv ./libft/libft.a .
			${CC} -fsanitize=address -g -o ${NAME} ${OBJS} ${FRAMEWORK}
			#${CC} -fsanitize=address -g -o ${NAME} ${OBJS} ${FRAMEWORK}
			#COMPILAR LINUX ${CC} -fsanitize=address ${LIBS} -o $(NAME) ${OBJS} ${FRAMEWORK}

all:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./mlx
			${MAKE} clean -C ./libft

fclean : 	clean
			${RM} ${NAME} libmlx.a libft.a

re:			fclean all

.PHONY:		re all clean fclean