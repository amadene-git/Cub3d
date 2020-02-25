/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:32:59 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:16:44 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int		convert_xmp_to_data(t_cub *s, t_image *tex, int i, int j)
{
	tex->img_ptr = mlx_xpm_file_to_image(s->mlx_ptr,\
	(s->parsing[i] + j), &tex->img_w, &tex->img_h);
	if (!tex->img_ptr)
		return (0);
	tex->data = (int*)mlx_get_data_addr(tex->img_ptr,\
	&tex->bit_pix, &tex->size_l, &tex->endian);
	return (1);
}

int		texture_n_init(t_cub *s)
{
	int i;
	int j;
	int n;

	i = -1;
	j = 2;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'N' && s->parsing[i][1] == 'O')
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
			if (!convert_xmp_to_data(s, &s->tex1, i, j))
				return (0);
			suppr_line(s->parsing, i);
			return (1);
		}
	return (0);
}

int		texture_s_init(t_cub *s)
{
	int i;
	int j;
	int n;

	i = -1;
	j = 2;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'S' && s->parsing[i][1] == 'O')
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
			if (!convert_xmp_to_data(s, &s->tex2, i, j))
				return (0);
			suppr_line(s->parsing, i);
			return (1);
		}
	return (0);
}

int		texture_e_init(t_cub *s)
{
	int i;
	int j;
	int n;

	i = -1;
	j = 2;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'E' && s->parsing[i][1] == 'A')
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
			if (!convert_xmp_to_data(s, &s->tex3, i, j))
				return (0);
			suppr_line(s->parsing, i);
			return (1);
		}
	return (0);
}

int		texture_w_init(t_cub *s)
{
	int i;
	int j;
	int n;

	i = -1;
	j = 2;
	while (s->parsing[++i])
		if (s->parsing[i][0] == 'W' && s->parsing[i][1] == 'E')
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
			if (!convert_xmp_to_data(s, &s->tex4, i, j))
				return (0);
			suppr_line(s->parsing, i);
			return (1);
		}
	return (0);
}
