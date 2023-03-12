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
				srcs/ft_atoi.c\
				srcs/ft_calloc.c\
				srcs/ft_isdigit.c\
				srcs/ft_isspace.c\
				srcs/ft_putstr.c\
				srcs/ft_strcmp.c\
				srcs/ft_suppr_char_str.c\
				srcs/gnl.c\
				srcs/gnl_utils.c\
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

OBJS		=	${SRCS:.c=.o}


HEADERSDIR 	=	inc

CFLAGS		=	-Wall -Wextra -Werror

CFLAGS		= 	-Wall -Werror -Wextra -g
INCLUDES	= 	-I$(HEADERSDIR) $(MLX)

PATH_MLX	=	./minilibx-linux/
MLX			= -L$(PATH_MLX) -lmlx -lXext -lX11 -lm


CC			=	gcc

RM			=	rm -rf



.c.o	:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all		:	${NAME}

${NAME}	:	${OBJS} 
				${CC} $(CFLAGS) -o ${NAME}  ${OBJS} $(INCLUDES)  

clean	:
				${RM} ${OBJS}

fclean	:	clean
				${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean sclean re ${NAME}
