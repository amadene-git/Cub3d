/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:25:13 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:16:09 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	raycaster(t_cub *s)
{
	t_raycaster r;
	int			stripe;

	r.x = -1;
	r.zbuffer = malloc(sizeof(double) * s->res_w + 1);
	while (++r.x < s->res_w)
		raycaster_texture(s, &r);
	sprite_init(s, &r);
	r.x = -1;
	while (++r.x < r.nbr_sprite)
		put_sprite(s, &r);
	free(r.zbuffer);
	free(s->sprite);
}
