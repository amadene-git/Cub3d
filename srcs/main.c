/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_notextured.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:12:34 by admadene          #+#    #+#             */
/*   Updated: 2020/02/12 17:02:00 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int		check_parsing(char **tab)
{
	int i;
	int j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (tab[i][j] != ' ')
				return (0);
	}
	return (1);
}

void	fct_save(t_cub *s)
{
	while (s->save++ < 10)
	{
		raycaster(s);
		s->dir.x = -cos(s->angle);
		s->dir.y = sin(s->angle);
		s->plane.x = s->dir.y * FOV;
		s->plane.y = -s->dir.x * FOV;
	}
	if ((ft_save("cub3D.bmp", s)) == -1)
		printf("shit\n");
	end_of_the_world(s, 10, "");
}

int		main(int ac, char **av)
{
	t_cub	s;
	int		err;

	s.mlx_ptr = mlx_init();
	err = 0;
	if ((ac == 3 && ft_strcmp(av[2], "--save")) ||\
	ac < 2 || ac > 3 || (err = stat_init(&s, av[1])))
	{
		error(&s, err);
		return (-1);
	}
	var_init(&s);
	if (ac == 3 && !ft_strcmp(av[2], "--save"))
		fct_save(&s);
	if (!check_parsing(s.parsing))
		error(&s, 1);
	mlx_hook(s.win_ptr, KEY_PRESSED, 0, handle_press, &s);
	mlx_hook(s.win_ptr, KEY_RELEASE, 0, handle_release, &s);
	mlx_loop_hook(s.mlx_ptr, move_print, &s);
	mlx_hook(s.win_ptr, DESTROY_NOTIFY, 0, close_win, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
