# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 11:10:51 by jtrancos          #+#    #+#              #
#    Updated: 2020/12/08 19:57:02 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= parse_file.c ./utils/parser_utils.c ./utils/GNL/get_next_line.c
OBJS		= ${SRCS:.c=.o}
NAME		= cub3D
CC			= gcc
RM			= rm -f
#CFLAGS		= -Werror -Wall -Wextra
FRAMEWORK	= -lz -L libft/ -lft
# MINILIB APPLE -L . -lmlx -framework AppKit -framework OpenGL 
# MINILIB LINUX -lmlx -lm -lbsd -lXext -lX11
LIBS		= -Lmlx_linux



.c.o:
			${CC} -g -c $< -o ${<:.c=.o}
			#gcc -o $@ -c $< $(CFLAGS)

${NAME}:	${OBJS}
			#${MAKE} -C ./mlx
			#${MAKE} -C ./mlx_linux
			${MAKE} -C ./libft
			#mv ./mlx/libmlx.a .
			#mv ./libft/libft.a .
			${CC} -fsanitize=address -g -o ${NAME} ${OBJS} ${FRAMEWORK}
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