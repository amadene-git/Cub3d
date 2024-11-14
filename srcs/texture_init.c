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

#include <cub.h>

int		convert_xmp_to_image(t_cub *s, t_image *image, char *pathToImage)
{
	image->img_ptr = mlx_xpm_file_to_image(s->mlx_ptr,\
	pathToImage, &image->img_w, &image->img_h);
	if (!image->img_ptr)
		return (0);
	image->data = (int*)mlx_get_data_addr(image->img_ptr,\
	&image->bit_pix, &image->size_l, &image->endian);
	return (1);
}

t_image	changeImageResolution(t_cub *s, t_image *image, int newWidth, int newHeight)
{
	t_image newImage;
	newImage.img_ptr = mlx_new_image(s->mlx_ptr, newWidth, newHeight);
	newImage.data = (int*)mlx_get_data_addr(newImage.img_ptr,\
	&newImage.bit_pix, &newImage.size_l, &newImage.endian);
	newImage.img_w = newWidth; 
	newImage.img_h = newWidth;
	
	int i = 0;
	while (i < newWidth * newHeight)
	{
		newImage.data[i] = image->data[(image->img_h * image->img_w * i) / (newWidth * newHeight)];
		++i;
	}
	mlx_destroy_image(s->mlx_ptr, image->img_ptr);
	return (newImage);
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
			if (!convert_xmp_to_image(s, &s->tex1, s->parsing[i] + j))
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
			if (!convert_xmp_to_image(s, &s->tex2, s->parsing[i] + j))
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
			if (!convert_xmp_to_image(s, &s->tex3, s->parsing[i] + j))
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
			if (!convert_xmp_to_image(s, &s->tex4, s->parsing[i] + j))
				return (0);
			suppr_line(s->parsing, i);
			return (1);
		}
	return (0);
}
