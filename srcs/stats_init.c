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

int		init_texsprite(t_cub *s)
{
	int i;
	int j;
	int n;

	i = -1;
	j = 1;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'S' && s->parsing[i][1] == ' ')
		{
			while (s->parsing[i][j] == ' ')
				j++;
			n = j;
			while (s->parsing[i][n] && s->parsing[i][n] != ' ')
				n++;
			if (!is_end_space(s->parsing[i] + n))
				return (0);
			s->parsing[i][n] = '\0';
			if (!check_file(s->parsing[i] + j))
				return (0);
			if (!convert_xmp_to_image(s, &s->texsprite, s->parsing[i] + j))
				return (0);
			suppr_line(s->parsing, i);
			return (1);
		}
	return (0);
}

void	sprite_nbr_init(t_cub *s, t_raycaster *r)
{
	int i;
	int j;

	i = 0;
	r->nbr_sprite = 0;
	while (i < s->mapheight)
	{
		j = 0;
		while (j < s->mapwidth)
		{
			if (s->worldmap[i][j++] == '2')
				r->nbr_sprite++;
		}
		i++;
	}
}

void	sprite_pos_init(t_cub *s, t_raycaster *r)
{
	int i;
	int j;
	int	n;

	i = 0;
	n = 0;
	s->sprite = (t_sprite*)malloc(sizeof(t_sprite) * r->nbr_sprite);
	while (i < s->mapheight)
	{
		j = 0;
		while (j < s->mapwidth)
		{
			if (s->worldmap[i][j++] == '2')
			{
				s->sprite[n].x = i + 0.5;
				s->sprite[n].y = j - 0.5;
				n++;
			}
		}
		i++;
	}
}

int		texture_init(t_cub *s)
{
	if (!texture_n_init(s) || !texture_s_init(s)\
	|| !texture_e_init(s) || !texture_w_init(s))
		return (0);
	return (1);
}

int		stat_init(t_cub *s, char *filename)
{
	if (!(s->parsing = parsing(filename)))
		end_of_the_world(s, 0, "Le parsing du fichier a echoue\n");
	if (!resolution_init(s))
		end_of_the_world(s, 0, "Resolution non valide\n");
	if (!texture_init(s))
		end_of_the_world(s, 0, "Textures murs non valide\n");
	if (!ceiling_init(s) || !floor_init(s))
		end_of_the_world(s, 0, "Plafond ou Sol non valide\n");
	if (!init_texsprite(s))
		end_of_the_world(s, 0, "Texture Sprite non valide\n");
	if (!check_map(s))
		end_of_the_world(s, 0, "Map non valide\n");
	s->pos_x = -1.0;
	s->pos_y = -1.0;
	if (!init_pos(s))
		end_of_the_world(s, 0, "position joueur non valide\n");
	return (0);
}
