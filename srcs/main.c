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

int	main(int ac, char **av)
{
	t_cub	s;
	int		err;

	s.mlx_ptr = mlx_init();
	err = 0;
	if ((ac == 3 && ft_strcmp(av[2], "--save")) ||\
	(ac < 2 && ac > 3) || (err = stat_init(&s, av[1])))
	{
		ft_putstr("Error\n");
		error(&s, err);
		return (-1);
	}
	var_init(&s);
	if (ac == 3 && !ft_strcmp(av[2], "--save"))
		s.save = 1;
	mlx_hook(s.win_ptr, KEY_PRESSED, 0, handle_press, &s);
	mlx_hook(s.win_ptr, KEY_RELEASE, 0, handle_release, &s);
	mlx_loop_hook(s.mlx_ptr, move_print, &s);
	mlx_hook(s.win_ptr, DESTROY_NOTIFY, 0, close_win, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
