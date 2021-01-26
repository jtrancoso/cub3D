# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 11:10:51 by jtrancos          #+#    #+#              #
#    Updated: 2021/01/26 14:04:14 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	cub3d.c\
				./utils/handle_error.c\
				./parser/parse_file.c\
				./parser/parse_texture.c\
				./parser/parse_resolution.c\
				./parser/parse_colour.c\
				./parser/parse_map.c\
				./parser/parser_utils.c\
				./parser/parser_misc.c\
				./utils/GNL/get_next_line.c\
				./raycasting/draw_texture.c\
				./raycasting/raycasting_utils.c\

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



.c. -lfto:
			${CC} -g -c $< -o ${<:.c=.o}
			#gcc -o $@ -c $< $(CFLAGS)

${NAME}:	${OBJS}
			${MAKE} -C ./mlx
			#${MAKE} -C ./mlx_linux
			${MAKE} -C ./libft
			mv ./mlx/libmlx.a .
			mv ./libft/libft.a .
			${CC} -g -o ${NAME} ${OBJS} ${FRAMEWORK}
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