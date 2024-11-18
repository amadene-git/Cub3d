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

SRCS		=	srcs/check_map_utils.c\
				srcs/init_close.c\
				srcs/main.c\
				srcs/move.c\
				srcs/put_sprite.c\
				srcs/put_texture.c\
				srcs/raycaster.c\
				srcs/raycaster_texture.c\
				srcs/save.c\
				srcs/initializeBackgroundColors.c\
				srcs/initializeConfig.c\
				srcs/initializeConfigResolution.c\
				srcs/initializeMap.c\
				srcs/initializeTextures.c\

OBJS		=	${SRCS:%.c=${DIR_OBJS}/%.o}

DIR_HEADER 	=	includes
DIR_SRCS	=	srcs
DIR_OBJS 	=	./objs
DIR_MLX		=	./minilibx-linux
DIR_LIBFT	=

CFLAGS		= 	-Wall -Werror -Wextra -g
DBFLAGS		=	-g
INCLUDES	= 	-I $(DIR_HEADER)
MLXFAGS		=	-L $(DIR_MLX) -lmlx -lXext -lX11 -lm

LIBFT		=	$(DIR_HEADER)/.libft.a
LIBFT_H		=	$(DIR_HEADER)/.libft.h

CC			=	gcc
RM			=	rm -rf

all		:	${LIBFT} ${DIR_OBJS} ${NAME} 

${NAME}	:	${OBJS}
				$(CC) $(CFLAGS) -o $@ $^ $(MLXFAGS) ${LIBFT}

${DIR_OBJS} :
				mkdir -p ${DIR_OBJS}/${DIR_SRCS}

${LIBFT} : 
			@if ! test -f ${LIBFT};\
			then\
				set -e;\
				git clone git@github.com:amadene-git/libft;\
				cd libft; make > /dev/null; cd ..;\
				mv libft/libft.a $(DIR_HEADER)/.libft.a;\
				mv libft/libft.h $(DIR_HEADER)/.libft.h;\
				rm -rf libft;\
			fi


${DIR_OBJS}/%.o	:	%.c
					$(CC) ${INCLUDES} $(CFLAGS) -c $< -o $@

clean	:
				${RM} ${OBJS} ${DIR_OBJS}

fclean	:	clean
				${RM} ${NAME}
lclean :	fclean
				${RM} ${LIBFT} $(LIBFT_H) libft

re		:	fclean all

.PHONY	:	all clean fclean re lclean 
