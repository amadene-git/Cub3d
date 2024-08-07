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

SRCS		=	srcs/check_map.c\
				srcs/check_map_utils.c\
				srcs/floor_ceiling_init.c\
				srcs/ft_suppr_char_str.c\
				srcs/init_close.c\
				srcs/main.c\
				srcs/move.c\
				srcs/parsing.c\
				srcs/put_sprite.c\
				srcs/put_texture.c\
				srcs/raycaster.c\
				srcs/raycaster_texture.c\
				srcs/res_init.c\
				srcs/save.c\
				srcs/stats_init.c\
				srcs/texture_init.c\

OBJS		=	${SRCS:%.c=${DIR_OBJS}/%.o}

DIR_HEADER 	=	./inc
DIR_SRCS	=	srcs
DIR_OBJS 	=	./objs
DIR_MLX		=	./minilibx-linux

CFLAGS		= 	-Wall -Werror -Wextra -I.
DBFLAGS		=	-g
INCLUDES	= 	-I$(DIR_HEADER) $(MLXFAGS)  
MLXFAGS		=	-L$(DIR_MLX) -lmlx -lXext -lX11 -lm

CC			=	gcc
RM			=	rm -rf
LIBFT		=	.libft.a

all		:	${LIBFT} ${DIR_OBJS} ${NAME} 

${NAME}	:	${OBJS}
				$(CC) $(CFLAGS) -o $@ $^ ${INCLUDES} ${LIBFT}

${DIR_OBJS} :
				mkdir -p ${DIR_OBJS}/${DIR_SRCS}

${LIBFT} : 
			@if ! test -f ${LIBFT};\
			then\
				set -e;\
				git clone git@github.com:amadene-git/libft;\
				cd libft; make > /dev/null; cd ..;\
				mv libft/libft.a .libft.a;\
				mv libft/libft.h .libft.h;\
				rm -rf libft;\
			fi


${DIR_OBJS}/%.o	:	%.c
					$(CC) $(CFLAGS) -c $< -o $@

clean	:
				${RM} ${OBJS} ${DIR_OBJS}

fclean	:	clean
				${RM} ${NAME}
lclean :	fclean
				${RM} ${LIBFT} .libft.h libft

re		:	fclean all

.PHONY	:	all clean fclean re lclean 
