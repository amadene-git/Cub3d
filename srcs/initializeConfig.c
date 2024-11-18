/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:38:14 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:16:38 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

char	*skipWhitespaces(char *str) {
	while (*str && ft_isspace(*str))
		++str;
	return (str);
}

void	freeTab(char **tab) {
	int i = 0;
	while (tab[i]) {
		free(tab[i]);
		++i;
	}
	free(tab);
}

void	printTab(char **tab) {
	for (int i = 0; tab[i]; ++i)
		printf("%d - '%s'\n", i, tab[i]);
}

int		checkFile(const char *filename, const char *extension)
{
	if (extension && *extension)
	{
		char *str = ft_strrchr(filename, '.');
		if (!*str++ && ft_strcmp(str, extension))
			return (0);
	}
	int fd;
	if ((fd = open(((const char*)(filename)), O_RDONLY)) == -1)
		return (0);
	close(fd);
	return (1);
}

char	**fileDuplicate(const char *filename)
{
	if (!checkFile(filename, ".cub"))
		return (NULL);

	return (ft_getFile(filename));
}


int		initializeConfig(t_cub *s, const char *filename) {
	s->_config._filename = filename;

	s->_config._fileDuplicate = fileDuplicate(s->_config._filename);
	if (s->_config._fileDuplicate == NULL)
		end_of_the_world(s, 0, "Configuration file Error: File reading failed\n");
	else {
		s->parsing = s->_config._fileDuplicate;
	}

	if (!initializeConfigResolution(&s->_config))
		end_of_the_world(s, 0, "Configuration file Error: Invalid resolution\n");
	else {
		s->res_w = s->_config._resolutionWidth;
		s->res_h = s->_config._resolutionHeight;
		s->render.img_w = s->_config._resolutionWidth;
		s->render.img_h = s->_config._resolutionHeight;
	}

	if (!initializeBackgroundColors(&s->_config))
		end_of_the_world(s, 0, "Configuration file Error: Invalid color for ceiling or floor\n");
	else {
		s->ceiling = s->_config._backgroundColor._ceiling;
		s->floor = s->_config._backgroundColor._floor;
	}

	if (!initializeTextures(s))
		end_of_the_world(s, 0, "Configuration file Error: Invalid textures settings\n");
	else {
		s->tex1 = s->_config._wallTexture._north;
		s->tex2 = s->_config._wallTexture._south;
		s->tex3 = s->_config._wallTexture._east;
		s->tex4 = s->_config._wallTexture._west;
		s->texsprite = s->_config._spriteTexture;
	}

	if (!initializeMap(s))
		end_of_the_world(s, 0, "Configuration file Error: Map non valide\n");
	else {
		s->worldmap = s->_config._map._tab;
		s->mapwidth = s->_config._map._width;
		s->mapheight = s->_config._map._height;
	}
	if (!init_pos(s))
		end_of_the_world(s, 0, "position joueur non valide\n");
	return (0);
}
