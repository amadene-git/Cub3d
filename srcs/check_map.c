/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:25:56 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:12:16 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	clean_space(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == ' ')
				tab[i] = suppr_char_string(tab[i], j);
			else
				j++;
		}
		i++;
	}
}

char	**map_parsing(t_cub *s)
{
	int		i;
	int		n;
	char	**worldmap;

	map_parsing_utils(s, &i, &n);
	if (!n)
		return (NULL);
	s->mapheight = n;
	if (!(worldmap = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	i -= n;
	n = 0;
	while (s->parsing[i])
	{
		worldmap[n++] = ft_strdup(s->parsing[i]);
		suppr_line(s->parsing, i);
	}
	worldmap[n] = NULL;
	clean_space(worldmap);
	return (worldmap);
}

int		check_char_in_map(char *str)
{
	while (*str)
	{
		if (*str != '0' && *str != '1'\
		&& *str != '2' && *str != 'W'\
		&& *str != 'E' && *str != 'S'\
		&& *str != 'N')
			return (0);
		str++;
	}
	return (1);
}

int		check_map(t_cub *s)
{
	int	i;
	int j;

	s->worldmap = map_parsing(s);
	s->mapwidth = ft_strlen(s->worldmap[0]);
	i = -1;
	while (++i < s->mapheight)
	{
		if ((int)ft_strlen(s->worldmap[i]) != s->mapwidth ||\
		s->worldmap[i][0] != '1' || s->worldmap[i][s->mapwidth - 1] != '1')
			return (0);
		if (!check_char_in_map(s->worldmap[i]))
			return (0);
	}
	j = 0;
	while (j < s->mapwidth)
		if (s->worldmap[0][j++] != '1')
			return (0);
	j = 0;
	while (j < s->mapwidth)
		if (s->worldmap[s->mapheight - 1][j++] != '1')
			return (0);
	return (1);
}

int		init_pos(t_cub *s)
{
	int i;
	int j;
	s->pos_x = -1.0;
	s->pos_y = -1.0;


	i = -1;
	while ((j = -1) && ++i < s->mapheight)
		while (++j < s->mapwidth)
			if (s->worldmap[i][j] == 'N' || s->worldmap[i][j] == 'S'\
			|| s->worldmap[i][j] == 'E' || s->worldmap[i][j] == 'W')
			{
				if (s->pos_y != -1.0 || s->pos_x != -1.0)
					return (0);
				init_pos_utils(s, i, j);
				s->worldmap[i][j] = '0';
			}
	if (s->pos_y != -1.0 || s->pos_x != -1.0)
		return (1);
	return (0);
}
