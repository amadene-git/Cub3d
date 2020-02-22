# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admadene <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/04 09:09:42 by admadene          #+#    #+#              #
#    Updated: 2020/02/04 09:09:44 by admadene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	cub3D

SRCS		=	$(wildcard srcs/*.c)

OBJS		=	${SRCS:.c=.o}

CFLAGS		=	-Wall -Wextra -Werror

MLXFLAGS	=	-I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

CC			=	gcc

RM			=	rm -rf



.c.o	:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all		:	${OBJS} 
				${CC} ${MLXFLAGS} -o ${NAME} ${OBJS} 

clean	:
				${RM} ${OBJS}

fclean	:	clean
				${RM} ${NAME}

sclean	:	fclean
			${RM} cub3D.bmp

re		:	fclean all

.PHONY	:	all clean fclean sclean re ${NAME}
