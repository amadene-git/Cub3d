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


NAME		=	Cub3D

SRCS		=	$(wildcard srcs/*.c)

OBJSDOSS	=	objs/

OBJS		=	${SRCS:.c=.o}

CFLAGS		=	-Wall -Wextra -Werror

MLXFLAGS	=	-I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

CC			=	gcc

RM			=	rm -rf



.c.o	:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all		:	${OBJS} 
				${CC} ${MLXFLAGS} -o ${NAME} ${OBJS} ; mkdir ${OBJSDOSS} ; mv ${OBJS} ${OBJSDOSS}

clean	:
				${RM} ${OBJSDOSS}

fclean	:	clean
				${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re ${NAME}
