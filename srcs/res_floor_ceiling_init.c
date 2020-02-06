/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_floor_ceiling_init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:39:23 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:16:24 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int		resolution_init(t_cub *s)
{
	int i;
	int j;

	i = -1;
	j = 1;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'R')
		{
			s->res_w = ft_atoi((s->parsing[i]) + 1);
			while (s->parsing[i][j] == ' ')
				j++;
			while (s->parsing[i][j] >= '0' && s->parsing[i][j] <= '9')
				j++;
			while (s->parsing[i][j] == ' ')
				j++;
			s->res_h = ft_atoi((s->parsing[i]) + j);
			if (s->res_w <= 0 || s->res_h <= 0)
				return (0);
			if (s->res_w > 2560)
				s->res_w = 2560;
			if (s->res_h > 1440)
				s->res_h = 1440;
			return (1);
		}
	return (0);
}

int		convert_color(int tab[3])
{
	int color;

	color = (int)tab[2];
	color += (int)tab[1] * 256;
	color += (int)tab[0] * 35536;
	return (color);
}

void	skip_digit(t_cub *s, int i, int *j)
{
	while (ft_isdigit(s->parsing[i][*j]))
		(*j)++;
}

int		ceiling_init(t_cub *s)
{
	int	i;
	int	j;
	int	tab[3];

	i = -1;
	j = 1;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'C')
		{
			while (s->parsing[i][j] == ' ')
				j++;
			tab[0] = ft_atoi(s->parsing[i] + j);
			skip_digit(s, i, &j);
			if (s->parsing[i][j++] != ',')
				return (0);
			tab[1] = ft_atoi(s->parsing[i] + j);
			skip_digit(s, i, &j);
			if (s->parsing[i][j++] != ',')
				return (0);
			tab[2] = ft_atoi(s->parsing[i] + j);
			s->ceiling = convert_color(tab);
			return (1);
		}
	return (0);
}

int		floor_init(t_cub *s)
{
	int	i;
	int	j;
	int	tab[3];

	i = -1;
	j = 1;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'F')
		{
			while (s->parsing[i][j] == ' ')
				j++;
			tab[0] = ft_atoi(s->parsing[i] + j);
			skip_digit(s, i, &j);
			if (s->parsing[i][j++] != ',')
				return (0);
			tab[1] = ft_atoi(s->parsing[i] + j);
			skip_digit(s, i, &j);
			if (s->parsing[i][j++] != ',')
				return (0);
			tab[2] = ft_atoi(s->parsing[i] + j);
			s->floor = convert_color(tab);
			return (1);
		}
	return (0);
}
