/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 09:56:25 by admadene          #+#    #+#             */
/*   Updated: 2020/02/22 09:56:26 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	skip_space(t_cub *s, int i, int *j)
{
	while (s->parsing[i][*j] == ' ')
		(*j)++;
}

int		end_of_fct(t_cub *s, int *i, int *j)
{
	skip_digit(s, *i, j);
	if (!is_end_space(s->parsing[*i] + *j))
		return (0);
	suppr_line(s->parsing, *i);
	return (1);
}

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
			skip_space(s, i, &j);
			skip_digit(s, i, &j);
			skip_space(s, i, &j);
			s->res_h = ft_atoi((s->parsing[i]) + j);
			if (s->res_w <= 0 || s->res_h <= 0)
				return (0);
			if (s->res_w > 2560 || s->res_h > 1440)
			{
				s->res_w = 2560;
				s->res_h = 1440;
			}
			s->render.img_w = s->res_w;
			s->render.img_h = s->res_h;
			return (end_of_fct(s, &i, &j));
		}
	return (0);
}
