/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:28:51 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:15:38 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	move_up_down(t_cub *s)
{
	if (s->key.up || s->key.w)
	{
        if (s->worldmap[(int)(s->pos_x + s->dir.x * (MOVE_SPEED\
		+ s->key.shift))][(int)(s->pos_y)] != '1')
			s->pos_x += s->dir.x * (MOVE_SPEED + s->key.shift);
		if (s->worldmap[(int)(s->pos_x)][(int)(s->pos_y +\
		s->dir.y * (MOVE_SPEED + s->key.shift))] != '1')
			s->pos_y += s->dir.y * (MOVE_SPEED + s->key.shift);
	}
	if (s->key.down || s->key.s)
	{
		if (s->worldmap[(int)(s->pos_x - s->dir.x * (MOVE_SPEED\
		+ s->key.shift))][(int)(s->pos_y)] != '1')
			s->pos_x -= s->dir.x * (MOVE_SPEED + s->key.shift);
		if (s->worldmap[(int)(s->pos_x)][(int)(s->pos_y - s->dir.y\
		* (MOVE_SPEED + s->key.shift))] != '1')
			s->pos_y -= s->dir.y * (MOVE_SPEED + s->key.shift);
	}
}

void	move_key(t_cub *s)
{
	if (s->key.up || s->key.w || s->key.down || s->key.s)
		move_up_down(s);
	if (s->key.a)
	{
		if (s->worldmap[(int)(s->pos_x - s->dir.y * (MOVE_SPEED\
		+ s->key.shift))][(int)(s->pos_y)] != '1')
			s->pos_x -= s->dir.y * (MOVE_SPEED + s->key.shift);
		if (s->worldmap[(int)(s->pos_x)][(int)(s->pos_y +\
		s->dir.x * (MOVE_SPEED + s->key.shift))] != '1')
			s->pos_y += s->dir.x * (MOVE_SPEED + s->key.shift);
	}
	if (s->key.d)
	{
		if (s->worldmap[(int)(s->pos_x + s->dir.y * (MOVE_SPEED\
		+ s->key.shift))][(int)(s->pos_y)] != '1')
			s->pos_x += s->dir.y * (MOVE_SPEED + s->key.shift);
		if (s->worldmap[(int)(s->pos_x)][(int)(s->pos_y - s->dir.x\
		* (MOVE_SPEED + s->key.shift))] != '1')
			s->pos_y -= s->dir.x * (MOVE_SPEED + s->key.shift);
	}
	if (s->key.left)
		s->angle -= M_PI / ROT_SPEED;
	if (s->key.right)
		s->angle += M_PI / ROT_SPEED;
}

int		handle_press(int key_pressed, t_cub *s)
{

    if (key_pressed == UP_KEY)
		s->key.up = 1;
	if (key_pressed == DOWN_KEY)
		s->key.down = 1;
	if (key_pressed == LEFT_KEY)
		s->key.left = 1;
	if (key_pressed == RIGHT_KEY)
		s->key.right = 1;
	if (key_pressed == W_KEY)
		s->key.w = 1;
	if (key_pressed == A_KEY)
		s->key.a = 1;
	if (key_pressed == S_KEY)
		s->key.s = 1;
	if (key_pressed == D_KEY)
		s->key.d = 1;
	if (key_pressed == ESCAPE_KEY)
		end_of_the_world(s, 10, "");
	return (1);
}

int		handle_release(int key_release, t_cub *s)
{
	if (key_release == UP_KEY)
		s->key.up = 0;
	if (key_release == DOWN_KEY)
		s->key.down = 0;
	if (key_release == LEFT_KEY)
		s->key.left = 0;
	if (key_release == RIGHT_KEY)
		s->key.right = 0;
	if (key_release == W_KEY)
		s->key.w = 0;
	if (key_release == A_KEY)
		s->key.a = 0;
	if (key_release == S_KEY)
		s->key.s = 0;
	if (key_release == D_KEY)
		s->key.d = 0;
	return (1);
}

void	putMinimapWall(t_cub *s, int **minimap) {
	for (size_t y = 0; y < MINIMAP_HEIGHT; ++y)
		for (size_t x = 0; x < MINIMAP_WIDTH; ++x) {
			size_t mapX = (x * s->_config._map._width) / MINIMAP_WIDTH;
			size_t mapY = (y * s->_config._map._height) / MINIMAP_HEIGHT;
			minimap[y][x] = (s->_config._map._tab[mapY][mapX] - '0') ? 0 : 0xFFFFFFFF;
		}
}

void	putMinimapPlayer(t_cub *s, int **minimap) {
	size_t minimapY = s->_player.y * MINIMAP_HEIGHT / s->_config._map._height;
	size_t minimapX = s->_player.x * MINIMAP_WIDTH / s->_config._map._width;
	size_t playerRadius = MINIMAP_HEIGHT / 100 + MINIMAP_WIDTH / 100;
	for (size_t y = minimapY - playerRadius; y < minimapY + playerRadius; ++y)
		for (size_t x = minimapX - playerRadius; x < minimapX + playerRadius; ++x)
			minimap[y][x] = 0x00FF0000;
}

void	putRenderMinimap(t_cub *s)
{
	int *tab = s->render.data;
	int **minimap = s->_minimap;

	putMinimapWall(s, minimap);
	putMinimapPlayer(s, minimap);
	for (size_t y = 0; y < MINIMAP_HEIGHT; ++y)
		for (size_t x = 0; x < MINIMAP_WIDTH; ++x)
			tab[(y * s->_config._resolutionWidth) + x] = minimap[y][x];
}

int		mainLoop(t_cub *s)
{
	raycaster(s);

	s->_player.x = s->pos_y;
	s->_player.y = s->pos_x;
	s->_player.dirX = s->dir.y;
	s->_player.dirY = s->dir.x;
	// printf("x %f\n", s->_player.x);
	// printf("y %f\n", s->_player.y);
	// printf("angle %f\n", s->angle);
	// printf("angle tan %f\n", acos(s->_player.dirY));
	// printf("dirx %f\n", s->_player.dirX);
	// printf("diry %f\n", s->_player.dirY);
	// printf("\n");
	putRenderMinimap(s);


	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->render.img_ptr, 0, 0);
	s->dir.x = -cos(s->angle);
	s->dir.y = sin(s->angle);
	s->plane.x = s->dir.y * FOV;
	s->plane.y = -s->dir.x * FOV;
	move_key(s);
	if (s->save)
	{
		ft_save("Cub3D.bmp", s);
		end_of_the_world(s, 10, "");
	}
	return (0);
}
