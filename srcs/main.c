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

#include <cub.h>

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
	ft_save("cub3d.bmp", s);
	end_of_the_world(s, 10, "");
}

int		main(int ac, char **av)
{
	t_cub	s;

	if ((ac == 3 && ft_strcmp(av[2], "--save"))) {
		printUsage("Error: invalid option\n\n");
		end_of_the_world(&s, 0, "");
	}
	if (ac < 2 || ac > 3) {
		printUsage("Error: one argument required\n\n");
		end_of_the_world(&s, 0, "");
	}


	s.win_ptr = NULL;
	s.mlx_ptr = mlx_init();

	initializeConfig(&s, av[1]);

	s.save = (ac == 3 && !ft_strcmp(av[2], "--save"));
	var_init(&s);
	if (s.save)
		fct_save(&s);
	if (!check_parsing(s.parsing))
		end_of_the_world(&s, 1, "");
	
	mlx_hook(s.win_ptr, KEY_PRESSED, (1L << 0), handle_press, &s);
	mlx_hook(s.win_ptr, KEY_RELEASE, (1L << 1), handle_release, &s);
	mlx_loop_hook(s.mlx_ptr, move_print, &s);
	mlx_hook(s.win_ptr, DESTROY_NOTIFY, (1L << 17), close_win, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}



// #include "mlx.h"
// #include <stdio.h>
/*
a 0
s 1
d 2
w 13
space 49
esc 53
left 123
right 124
down 125
up 126
lcontrol 256
lcommand 259
lshift 257
rcommand 260
rcontrol 269
rshift 258


*/
// int		number_of_key(int key, void *params)
// {
// 	printf("%d\n", key);
//     (void)params;
// 	return (0);
// }

// int main()
// {
// 	void	*mlx_ptr = mlx_init();
// 	void	*win_ptr = mlx_new_window(mlx_ptr, 100, 100, "titre");
	
// 	mlx_key_hook(win_ptr, number_of_key, NULL);
// 	mlx_loop(mlx_ptr);

// }