/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasteur_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:22:54 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:16:15 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int lol = 0;

void	raycaster_init(t_raycaster *r, t_cub *s)
{
	r->camerax = 2 * r->x / (double)(s->res_w) - 1;
	r->raydirx = s->dir.x + s->plane.x * r->camerax;
	r->raydiry = s->dir.y + s->plane.y * r->camerax;
	r->mapx = (int)(s->pos_x);
	r->mapy = (int)(s->pos_y);
	r->deltadistx = fabs(1 / r->raydirx);
	r->deltadisty = fabs(1 / r->raydiry);
	r->hit = 0;
}

void	raycaster_dda(t_raycaster *r, t_cub *s)
{
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (s->pos_x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - s->pos_x) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (s->pos_y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - s->pos_y) * r->deltadisty;
	}
}

void	raycaster_algo(t_raycaster *r, t_cub *s)
{
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (s->worldmap[r->mapx][r->mapy] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perpwalldist = (r->mapx - s->pos_x +\
				(1 - r->stepx) / 2) / r->raydirx;
	else
		r->perpwalldist = (r->mapy - s->pos_y +\
				(1 - r->stepy) / 2) / r->raydiry;
	r->lineheight = (int)(s->res_h / r->perpwalldist);
	r->drawstart = -r->lineheight / 2 + s->res_h / 2;
}

void	raycaster_texture(t_cub *s, t_raycaster *r)
{
	raycaster_init(r, s);
	raycaster_dda(r, s);
	raycaster_algo(r, s);
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + s->res_h / 2;
	if (r->drawend >= s->res_h)
		r->drawend = s->res_h - 1;
	if (r->side == 0)
		r->wallx = s->pos_y + r->perpwalldist * r->raydiry;
	else
		r->wallx = s->pos_x + r->perpwalldist * r->raydirx;
	r->wallx -= floor((r->wallx));
	if (r->side == 0 && r->raydirx < 0)
		put_texture_s(r, s);
	else if (r->side == 0)
		put_texture_n(r, s);
	else if (r->side == 1 && r->raydiry < 0)
		put_texture_e(r, s);
	else if (r->side == 1)
		put_texture_w(r, s);
	r->zbuffer[r->x] = r->perpwalldist;
}
