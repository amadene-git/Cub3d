/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 10:30:34 by admadene          #+#    #+#             */
/*   Updated: 2020/02/22 10:30:35 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	init_pos_utils(t_cub *s, int i, int j)
{
	s->pos_x = i + 0.5;
	s->pos_y = j + 0.5;
	if (s->worldmap[i][j] == 'N')
		s->angle = 0;
	if (s->worldmap[i][j] == 'S')
		s->angle = M_PI;
	if (s->worldmap[i][j] == 'E')
		s->angle = M_PI / 2;
	if (s->worldmap[i][j] == 'W')
		s->angle = M_PI + (M_PI / 2);
}
