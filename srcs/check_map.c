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

static size_t	findMapFieldIndex(char **fileDuplicate)
{
	for (size_t i = 0; fileDuplicate[i]; ++i) {
		if (!ft_strncmp(skipWhitespaces(fileDuplicate[i]), "MAP", ft_strlen("MAP")))
			return (i + 1);
	}
	return (-1);
}

static int		computeMapHeight(char **mapTab) {
	int	mapHeight = 0;
	while (*mapTab && *skipWhitespaces(*mapTab) == '1') {
		++mapHeight;
		++mapTab;
	}
	return (mapHeight);
}

static char		*ft_strdupWithoutWhitespaces(const char *str) {
	size_t	len = ft_strlen(str);
	char	ret[len];
	ft_bzero(ret, len);

	int i = 0;
	while (*str) {
		if (!ft_isspace(*str)) {
			ret[i] = *str;
			++i;
		}
		++str;
	}
	ret[i] = '\0';
	return (ft_strdup(ret));
}

static char		**createMapTab(char **mapTab, size_t mapHeight) {
	char	**mapTabCopy = NULL;
	
	if (!(mapTabCopy = (char**)malloc(sizeof(char*) * (mapHeight + 1))))
		return (NULL);
	for (size_t i = 0; i < mapHeight; ++i) {
		mapTabCopy[i] = ft_strdupWithoutWhitespaces(mapTab[i]);
	}
	mapTabCopy[mapHeight] = NULL;
	return (mapTabCopy);
}

int				map_parsing(t_cub *s)
{
	s->_config._map._tab = NULL;	
	int mapIndex = findMapFieldIndex(s->_config._fileDuplicate);
	if (mapIndex == -1)
		return (0);
	if (!(s->_config._map._height = computeMapHeight(s->_config._fileDuplicate + mapIndex)))
		return (0);
	if (!(s->_config._map._tab = createMapTab(s->_config._fileDuplicate + mapIndex,
											s->_config._map._height)))
		return (0);
	s->_config._map._width = ft_strlen(s->_config._map._tab[0]);
	return (1);
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

	if (!map_parsing(s))
		return (0);
	s->worldmap = s->_config._map._tab;
	s->mapwidth = s->_config._map._width;
	s->mapheight = s->_config._map._height;
	i = -1;
	while (++i < s->mapheight)
	{
		if ((int)ft_strlen(s->worldmap[i]) != s->mapwidth ||
		s->worldmap[i][0] != '1' || s->worldmap[i][s->mapwidth - 1] != '1') {
	
			return (0);

		}
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
