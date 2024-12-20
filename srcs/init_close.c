/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:00:19 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:15:22 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	eotw_utils(t_cub *s)
{
	int i;

	i = 0;
	while (s->worldmap[i])
	{
		free(s->worldmap[i]);
		i++;
	}
	free(s->worldmap[i]);
}

void	end_of_the_world(t_cub *s, int err, char *str)
{
	int	i;

	i = 0;
	if (err > 1)
	{
		while (s->parsing[i])
		{
			free(s->parsing[i]);
			i++;
		}
		free(s->parsing[i]);
	}
	if (err > 5)
		eotw_utils(s);
	ft_putstr(str);

	if (s->win_ptr)
		mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_display(s->mlx_ptr);
	if (err == 10)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	var_init(t_cub *s)
{
	if (!s->save)
		s->win_ptr = mlx_new_window(s->mlx_ptr, s->res_w, s->res_h, "Cub3D");
	s->key.up = 0;
	s->key.down = 0;
	s->key.left = 0;
	s->key.right = 0;
	s->key.w = 0;
	s->key.a = 0;
	s->key.s = 0;
	s->key.d = 0;
	s->key.shift = 0.0;
	s->dir.x = 0.0;
	s->dir.y = 0.0;
	s->plane.x = 0.0;
	s->plane.y = 0.0;
	s->render.img_ptr = mlx_new_image(s->mlx_ptr, s->res_w, s->res_h);
	s->render.data = (int*)mlx_get_data_addr(s->render.img_ptr,\
	&s->render.bit_pix, &s->render.size_l, &s->render.endian);

	s->_minimap = malloc(sizeof(int*) * MINIMAP_HEIGHT);
	for (size_t i = 0; i < MINIMAP_HEIGHT; ++i)
	{
		s->_minimap[i] = malloc(sizeof(int) * MINIMAP_WIDTH);
		ft_bzero(s->_minimap[i], sizeof(int) * MINIMAP_WIDTH);
	}
}

void printUsage(char *message)
{
	ft_putstr(message);
	ft_putstr("Usage : ./cub3d FILE [--save]\n");
	ft_putstr("FILE: path to .cub configuration file\n");
	ft_putstr(" --save,\toption to screenshot 1rst frame\n");
}

int		close_win(t_cub *s)
{
	end_of_the_world(s, 10, "");
	return (0);
}
