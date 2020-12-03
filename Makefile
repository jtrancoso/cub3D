# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 11:10:51 by jtrancos          #+#    #+#              #
#    Updated: 2020/12/02 13:35:13 by jtrancos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= parser.c
OBJS		= ${SRCS:.c=.o}
NAME		= cub3D
CC			= gcc
RM			= rm -f
CFLAGS		= -Wno-deprecated-declarations
#NOERROR		= -Wno-all -Wno-error -Wno-extra -Wno-deprecated
FRAMEWORK	= -lz -L . -lmlx -L libft/ -lft -framework OpenGL -framework AppKit
#-lmlx -lm -lbsd -lXext -lX11
LIBS		= -Lmlx_linux



.c.o:
			${CC} -g -c $< -o ${<:.c=.o}
			#gcc -o $@ -c $< $(CFLAGS)

${NAME}:	${OBJS}
			${MAKE} -C ./mlx
			#${MAKE} -C ./mlx_linux
			${MAKE} -C ./libft
			#mv ./mlx/libmlx.a .
			#mv ./libft/libft.a .
			${CC} -fsanitize=address -g -o ${NAME} ${OBJS} ${FRAMEWORK}
			#${CC} -fsanitize=address ${LIBS} -o $(NAME) ${OBJS} ${FRAMEWORK} 

all:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./mlx
			${MAKE} clean -C ./libft

fclean : 	clean
			${RM} ${NAME} libmlx.a libft.a

re:			fclean all

.PHONY:		re all clean fclean