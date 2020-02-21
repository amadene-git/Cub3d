/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:52:48 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:15:54 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	swap(t_sprite *a, t_sprite *b)
{
	int swp;

	swp = a->order;
	a->order = b->order;
	b->order = swp;
}

void	sortsprites(t_sprite *sprite, int nbr_sprite)
{
	int i;
	int j;

	i = nbr_sprite - 1;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (sprite[j].sprite_dist < sprite[j + 1].sprite_dist)
				swap(&sprite[j], &sprite[j + 1]);
			j++;
		}
		i--;
	}
}

void	sprite_init(t_cub *s, t_raycaster *r)
{
	int i;

	i = 0;
	sprite_nbr_init(s, r);
	sprite_pos_init(s, r);
	while (i < r->nbr_sprite)
	{
		s->sprite[i].order = i;
		s->sprite[i].sprite_dist = ((s->pos_x - s->sprite[i].x)\
				* (s->pos_x - s->sprite[i].x) + (s->pos_y - s->sprite[i].y)\
				* (s->pos_y - s->sprite[i].y));
		i++;
	}
	sortsprites(s->sprite, r->nbr_sprite);
}

void	sprite_var_init(t_cub *s, t_raycaster *r)
{
	r->spritex = s->sprite[s->sprite[r->x].order].x - s->pos_x;
	r->spritey = s->sprite[s->sprite[r->x].order].y - s->pos_y;
	r->invdet = 1.0 / (s->plane.x * s->dir.y - s->dir.x * s->plane.y);
	r->transformx = r->invdet * (s->dir.y * r->spritex - s->dir.x\
			* r->spritey);
	r->transformy = r->invdet * (-s->plane.y * r->spritex + s->plane.x\
			* r->spritey);
	r->spritescreenx = (int)((s->res_w / 2) * (1 + r->transformx\
	/ r->transformy));
	r->spriteheight = abs((int)(s->res_h / (r->transformy)));
	r->drawstarty = -r->spriteheight / 2 + s->res_h / 2;
	if (r->drawstarty < 0)
		r->drawstarty = 0;
	r->drawendy = r->spriteheight / 2 + s->res_h / 2;
	if (r->drawendy >= s->res_h)
		r->drawendy = s->res_h - 1;
	r->spritewidth = abs((int)(s->res_h / (r->transformy) * 0.8));
	r->drawstartx = -r->spritewidth / 2 + r->spritescreenx;
	if (r->drawstartx < 0)
		r->drawstartx = 0;
	r->drawendx = r->spritewidth / 2 + r->spritescreenx;
	if (r->drawendx >= s->res_w)
		r->drawendx = s->res_w - 1;
}

void	put_sprite(t_cub *s, t_raycaster *r)
{
	int stripe;
	int y;

	sprite_var_init(s, r);
	stripe = r->drawstartx;
	while (stripe < r->drawendx)
	{
		r->texx = (int)(256 * (stripe - (-r->spritewidth / 2\
		+ r->spritescreenx)) * s->texsprite.img_w / r->spritewidth) / 256;
		if (r->transformy > 0 && stripe > 0 && stripe < s->res_w\
				&& r->transformy < r->zbuffer[stripe])
			y = r->drawstarty;
		while (y < r->drawendy)
		{
			r->d = y * 256 - s->res_h * 128 + r->spriteheight * 128;
			r->texy = ((r->d * s->texsprite.img_h) / r->spriteheight) / 256;
			if ((s->texsprite.data[s->texsprite.img_w * r->texy + r->texx]\
						& 0x00FFFFFF) != 0)
				s->render.data[y * s->res_w + stripe] =\
				s->texsprite.data[s->texsprite.img_w * r->texy + r->texx];
			y++;
		}
		stripe++;
	}
}
