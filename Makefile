# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 11:10:51 by jtrancos          #+#    #+#              #
#    Updated: 2020/11/04 14:03:02 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= lodev.c
OBJS		= ${SRCS:.c=.o}
NAME		= cub3d
CC			= cc
RM			= rm -f
CFLAGS		= #-Wall -Werror -Wextra
FRAMEWORK	= -lz -L . -lmlx -framework OpenGL -framework AppKit

.c.o:
			${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${MAKE} -C ./mlx
			#${MAKE} -C ./libft
			#mv ./minilibx/libmlx.a .
			#mv ./libft/libft.a .
			${CC} -fsanitize=address -g -o ${NAME} ${OBJS} ${FRAMEWORK}

all:		${NAME}

clean:
			${RM} ${OBJS}
#			${MAKE} clean -C ./minilibx
#			${MAKE} clean -C ./libft

fclean : 	clean
			${RM} ${NAME} libmlx.a 

re:			fclean all

.PHONY:		re all clean fclean