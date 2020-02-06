/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:55:30 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:16:30 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	write_int(t_frame_saver *sv, unsigned int val)
{
	sv->buf[sv->index++] = val >> 0;
	sv->buf[sv->index++] = val >> 8;
	sv->buf[sv->index++] = val >> 16;
	sv->buf[sv->index++] = val >> 24;
}

static void	write_file_header(t_frame_saver *sv)
{
	sv->buf[sv->index++] = 'B';
	sv->buf[sv->index++] = 'M';
	write_int(sv, sv->size);
	write_int(sv, 0x00000000);
	sv->buf[sv->index++] = 54;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 0;
}

static void	write_file_info(t_frame_saver *sv, t_cub *s)
{
	int i;

	sv->buf[sv->index++] = 40;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 0;
	write_int(sv, s->res_w);
	write_int(sv, s->res_h);
	sv->buf[sv->index++] = 1;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 24;
	sv->buf[sv->index++] = 0;
	i = 0;
	while (i < 24)
	{
		sv->buf[sv->index++] = 0;
		i++;
	}
}

static void	write_body(t_frame_saver *sv, t_cub *s)
{
	int x;
	int y;
	int *img_buff;

	img_buff = s->render.data;
	y = s->res_h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < s->res_w)
		{
			sv->buf[sv->index++] = img_buff[y * s->res_w + x] >> 0;
			sv->buf[sv->index++] = img_buff[y * s->res_w + x] >> 8;
			sv->buf[sv->index++] = img_buff[y * s->res_w + x] >> 16;
			x++;
		}
		x = 0;
		while (x < (4 - (s->res_w * 3) % 4) % 4)
		{
			sv->buf[sv->index++] = 0;
			x++;
		}
		y--;
	}
}

int			ft_save(char *filename, t_cub *s)
{
	int				fd;
	t_frame_saver	sv;

	sv = (t_frame_saver) {0};
	sv.size = 54 + 3 * s->res_w * s->res_h +
		((4 - (s->res_w * 3) % 4) % 4) * s->res_h;
	sv.buf = calloc(sv.size, 1);
	if ((fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR)) < 0)
		return (-1);
	write_file_header(&sv);
	write_file_info(&sv, s);
	write_body(&sv, s);
	write(fd, sv.buf, sv.size);
	free(sv.buf);
	close(fd);
	return (0);
}
