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

static int	convert_xpm_to_image(void *mlx_ptr, t_image *image, char *pathToImage)
{
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, pathToImage, &image->img_w, &image->img_h);
	if (!image->img_ptr)
		return (0);
	image->data = (int*)mlx_get_data_addr(image->img_ptr,\
	&image->bit_pix, &image->size_l, &image->endian);
	return (1);
}

static int	initializeTextureByTagName(t_cub *s, const char *tag, t_image *wallTexture) {
	char	**tokenizeLine = NULL;

	for (int i = 0; s->_config._fileDuplicate[i]; ++i) {
		if (ft_strncmp(skipWhitespaces(s->_config._fileDuplicate[i]), tag, ft_strlen(tag)) == 0) {
			tokenizeLine = ft_split_charset(s->_config._fileDuplicate[i], WHITESPACE_CHARSET);
			if (ft_strcmp(tokenizeLine[0], tag) != 0) {
				freeTab(tokenizeLine);
				continue;
			}
			if (tokenizeLine[1] == NULL
			  || tokenizeLine[2] != NULL
			  || !checkFile(tokenizeLine[1], "xpm")
			  || !convert_xpm_to_image(s->mlx_ptr, wallTexture, tokenizeLine[1]))
				return (0);
			freeTab(tokenizeLine);
			return (1);
		}
	}
	return (0);
}

int			initializeTextures(t_cub *s) {
	if (!initializeTextureByTagName(s, "NO", &s->_config._wallTexture._north)
	  || !initializeTextureByTagName(s, "SO", &s->_config._wallTexture._south)
	  || !initializeTextureByTagName(s, "WE", &s->_config._wallTexture._west)
	  || !initializeTextureByTagName(s, "EA", &s->_config._wallTexture._east)
	  || !initializeTextureByTagName(s, "S", &s->_config._spriteTexture))
		return (0);
	return (1);
}
