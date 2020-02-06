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


NAME	=	Cub3D

SRCS	=	lol

OBJS	=	${SRCS:.c=.o }

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

RM		=	rm -rf



.c.o	:
        		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all		:	${OBJS} 
            	${CC} -o ${NAME} ${OBJS}

clean	:
                ${RM} ${OBJS}

fclean	:	clean
        		${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re ${NAME}
