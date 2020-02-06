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

int		check_file(char *filename)
{
	int fd;

	if ((fd = open(((const char*)(filename)), O_RDONLY)) == -1)
		return (0);
	close(fd);
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
			s->parsing[i][n] = '\0';
			if (!check_file(s->parsing[i] + j))
				return (0);
			s->tex1.img_ptr = mlx_xpm_file_to_image(s->mlx_ptr,\
			(s->parsing[i] + j), &s->tex1.img_w, &s->tex1.img_h);
			s->tex1.data = (int*)mlx_get_data_addr(s->tex1.img_ptr,\
			&s->tex1.bit_pix, &s->tex1.size_l, &s->tex1.endian);
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
			s->parsing[i][n] = '\0';
			if (!check_file(s->parsing[i] + j))
				return (0);
			s->tex2.img_ptr = mlx_xpm_file_to_image(s->mlx_ptr,\
			(s->parsing[i] + j), &s->tex2.img_w, &s->tex2.img_h);
			s->tex2.data = (int*)mlx_get_data_addr(s->tex2.img_ptr,\
			&s->tex2.bit_pix, &s->tex2.size_l, &s->tex2.endian);
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
			s->parsing[i][n] = '\0';
			if (!check_file(s->parsing[i] + j))
				return (0);
			s->tex3.img_ptr = mlx_xpm_file_to_image(s->mlx_ptr,\
			(s->parsing[i] + j), &s->tex3.img_w, &s->tex3.img_h);
			s->tex3.data = (int*)mlx_get_data_addr(s->tex3.img_ptr,\
			&s->tex3.bit_pix, &s->tex3.size_l, &s->tex3.endian);
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
			s->parsing[i][n] = '\0';
			if (!check_file(s->parsing[i] + j))
				return (0);
			s->tex4.img_ptr = mlx_xpm_file_to_image(s->mlx_ptr,\
			(s->parsing[i] + j), &s->tex4.img_w, &s->tex4.img_h);
			s->tex4.data = (int*)mlx_get_data_addr(s->tex4.img_ptr,\
			&s->tex4.bit_pix, &s->tex4.size_l, &s->tex4.endian);
			return (1);
		}
	return (0);
}
