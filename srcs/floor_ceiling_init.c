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

int		skip_digit(t_cub *s, int i, int *j)
{
	int	n;

	n = *j;
	while (ft_isdigit(s->parsing[i][*j]))
	{
		printf("j %d\n", *j);
		(*j)++;
	}
	printf ("n %d ; j %d\n", n, *j);
	if (n == *j)
		return (0);
	return (1);
}

int		convert_color(t_cub *s, int *i, int *j, char *ptr)
{
	while (s->parsing[*i][*j] == ' ')
		(*j)++;
	if (ft_atoi(s->parsing[*i] + *j) > 255)
		return (0);
	*ptr-- = (char)ft_atoi(s->parsing[*i] + *j);
	if (!skip_digit(s, *i, j) || s->parsing[*i][(*j)++] != ',')
		return (0);
	printf ("lol\n");
	while (s->parsing[*i][*j] == ' ')
		(*j)++;
	if (ft_atoi(s->parsing[*i] + *j) > 255)
		return (0);
	*ptr-- = (char)ft_atoi(s->parsing[*i] + *j);
	if (!skip_digit(s, *i, j) || s->parsing[*i][(*j)++] != ',')
		return (0);
	while (s->parsing[*i][*j] == ' ')
		(*j)++;
	if (ft_atoi(s->parsing[*i] + *j) > 255)
		return (0);
	*ptr = (char)ft_atoi(s->parsing[*i] + *j);
	if (!skip_digit(s, *i, j))
		return (0);
	return (1);
}

int		ceiling_init(t_cub *s)
{
	int		i;
	int		j;
	char	*ptr;

	i = -1;
	j = 1;
	ptr = (char*)(&s->ceiling) + 2;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'C')
		{
			if (!convert_color(s, &i, &j, ptr))
				return (0);
			if (!is_end_space(s->parsing[i] + j))
				return (0);
			suppr_line(s->parsing, i);
			return (1);
		}
	return (0);
}

int		floor_init(t_cub *s)
{
	int		i;
	int		j;
	char	*ptr;

	i = -1;
	j = 1;
	ptr = (char*)(&s->floor) + 2;
	while (s->parsing[++i])
	{
		if (s->parsing[i][0] == 'F')
		{
			if (!convert_color(s, &i, &j, ptr))
				return (0);
			if (!is_end_space(s->parsing[i] + j))
				return (0);
			suppr_line(s->parsing, i);
			return (1);
		}
	}
	return (0);
}
