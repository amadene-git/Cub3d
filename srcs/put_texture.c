/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:15:48 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:16:03 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	put_texture_n(t_raycaster *r, t_cub *s)
{
	if (r->wallx != r->wallx)
		r->wallx = 0;
	r->texx = (int)(r->wallx * (double)(s->tex1.img_w));
	r->n = r->x;
	while (r->n < s->res_h * s->res_w)
	{
		if (r->n / s->res_w >= r->drawstart && r->n / s->res_w <= r->drawend)
		{
			if (r->lineheight > (r->drawend - r->drawstart + 1))
				r->texy = (int)(s->tex1.img_h * (((r->n / s->res_w)\
				- r->drawstart) + ((r->lineheight - s->res_h) / 2))\
				/ (r->lineheight + 1));
			else
				r->texy = (int)(s->tex1.img_h * ((r->n / s->res_w)\
				- r->drawstart) / (r->lineheight + 1));
			s->render.data[r->n] = s->tex1.data[r->texy\
			* s->tex1.img_w + r->texx];
		}
		else if (r->n / s->res_w < r->drawstart)
			s->render.data[r->n] = s->ceiling;
		else
			s->render.data[r->n] = s->floor;
		r->n += s->res_w;
	}
}

void	put_texture_s(t_raycaster *r, t_cub *s)
{
	if (r->wallx != r->wallx)
		r->wallx = 0;
	r->texx = (int)(r->wallx * (double)(s->tex2.img_w));
	r->n = r->x;
	while (r->n < s->res_h * s->res_w)
	{
		if (r->n / s->res_w >= r->drawstart && r->n / s->res_w <= r->drawend)
		{
			if (r->lineheight > (r->drawend - r->drawstart + 1))
				r->texy = (int)(s->tex2.img_h * (((r->n / s->res_w)\
				- r->drawstart) + ((r->lineheight - s->res_h) / 2))\
				/ (r->lineheight + 1));
			else
				r->texy = (int)(s->tex2.img_h * ((r->n / s->res_w)\
				- r->drawstart) / (r->lineheight + 1));
			s->render.data[r->n] = s->tex2.data[r->texy\
			* s->tex2.img_w + r->texx];
		}
		else if (r->n / s->res_w < r->drawstart)
			s->render.data[r->n] = s->ceiling;
		else
			s->render.data[r->n] = s->floor;
		r->n += s->res_w;
	}
}

void	put_texture_e(t_raycaster *r, t_cub *s)
{
	if (r->wallx != r->wallx)
		r->wallx = 0;
	r->texx = (int)(r->wallx * (double)(s->tex3.img_w));
	r->n = r->x;
	while (r->n < s->res_h * s->res_w)
	{
		if (r->n / s->res_w >= r->drawstart && r->n / s->res_w <= r->drawend)
		{
			if (r->lineheight > (r->drawend - r->drawstart + 1))
				r->texy = (int)(s->tex3.img_h * (((r->n / s->res_w)\
				- r->drawstart) + ((r->lineheight - s->res_h) / 2))\
				/ (r->lineheight + 1));
			else
				r->texy = (int)(s->tex3.img_h * ((r->n / s->res_w)\
				- r->drawstart) / (r->lineheight + 1));
			s->render.data[r->n] = s->tex3.data[r->texy\
			* s->tex3.img_w + r->texx];
		}
		else if (r->n / s->res_w < r->drawstart)
			s->render.data[r->n] = s->ceiling;
		else
			s->render.data[r->n] = s->floor;
		r->n += s->res_w;
	}
}

void	put_texture_w(t_raycaster *r, t_cub *s)
{
	if (r->wallx != r->wallx)
		r->wallx = 0;
	r->texx = (int)(r->wallx * (double)(s->tex4.img_w));
	r->n = r->x;
	while (r->n < s->res_h * s->res_w)
	{
		if (r->n / s->res_w >= r->drawstart && r->n / s->res_w <= r->drawend)
		{
			if (r->lineheight > (r->drawend - r->drawstart + 1))
				r->texy = (int)(s->tex4.img_h * (((r->n / s->res_w)\
				- r->drawstart) + ((r->lineheight - s->res_h) / 2))\
				/ (r->lineheight + 1));
			else
				r->texy = (int)(s->tex4.img_h * ((r->n / s->res_w)\
				- r->drawstart) / (r->lineheight + 1));
			s->render.data[r->n] = s->tex4.data[r->texy\
			* s->tex4.img_w + r->texx];
		}
		else if (r->n / s->res_w < r->drawstart)
			s->render.data[r->n] = s->ceiling;
		else
			s->render.data[r->n] = s->floor;
		r->n += s->res_w;
	}
}
