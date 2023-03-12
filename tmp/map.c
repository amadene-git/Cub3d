/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 15:17:58 by admadene          #+#    #+#             */
/*   Updated: 2019/12/09 15:18:00 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "X.h"
#include "get_next_line.h"
#include <libc.h>
#include <math.h>
#define CASE_W 50
#define WIN_H 24 * CASE_W
#define WIN_W 24 * CASE_W
#define UP_KEY 126
#define DOWN_KEY 125
#define LEFT_KEY 123
#define RIGHT_KEY 124
#define	MOVE_SPEED 0.2
#define	A_KEY 15
#define B_KEY 16


typedef	struct s_vector
{
	double	x;
	double	y;
}t_vector;

typedef struct 	s_cub
{
	double		pos_x;
	double		pos_y;
	int		start_x;
	int		start_y;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*data;
	char 	**map;
	double 	angle;
	t_vector	dir;
	t_vector	plane;

}				t_cub;




char	map[25][25] = {
						{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','2','2','2','2','2','0','0','0','0','3','0','3','0','3','0','0','0','1'},
  						{'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','3','0','0','0','3','0','0','0','1'},
  						{'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','2','2','0','2','2','0','0','0','0','3','0','3','0','3','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','4','4','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','4','0','4','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','4','0','0','0','0','5','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','4','0','4','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','4','0','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'}, 
  						{'1','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','4','4','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  						{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
						0
  						};

void	draw_sqrt(int x, int y, int weight, void *mlx_ptr, void *win_ptr, int color)
{
	int i;
	int j;

	i = x;
	j = y;
	while (y < weight + j)
	{
		x = i;
		while (x < weight + i)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

int abs (int n) 
{ 
    return (( n > 0) ? n : ( n * (-1))); 
} 
  
void 	draw_line(int X0, int Y0, int X1, int Y1, t_cub *s, int color) 
{  
    int steps = abs(X1 - X0) > abs(Y1 - Y0) ? abs(X1 - X0) : abs(Y1 - Y0); 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    { 
        mlx_pixel_put(s->mlx_ptr, s->win_ptr, X , Y, color); 
        X += (X1 - X0) / (float) steps; 
        Y += (Y1 - Y0) / (float) steps;
    } 
} 

void		draw_vector(t_vector v, double x, double y, t_cub *s, int color)
{
	double xb =  v.x + x;
	double yb =  v.y + y;
	draw_line(x * CASE_W,y * CASE_W, xb * CASE_W, yb * CASE_W, s, color);
}

t_vector	mutl_vector_k(t_vector v, double k)
{
	v.x *= k;
	v.y *= k;

	return (v);
}

void	draw_ray(t_cub *s)
{
	draw_vector(s->dir, s->pos_x, s->pos_y, s, 0xff0000);
	draw_vector(s->plane, s->pos_x + s->dir.x, s->pos_y + s->dir.y, s, 0x00ff00);
	draw_vector(mutl_vector_k(s->plane, -1), s->pos_x + s->dir.x, s->pos_y + s->dir.y, s, 0x00ffff);
}

int		handle_press(int key_pressed, t_cub *s)
{
	switch(key_pressed)
	{
		case UP_KEY :
			if (map[(int)s->pos_y][(int)s->pos_x] == '0')
			{
				s->pos_x += cos(s->angle) * 0.2;
				s->pos_y += -sin(s->angle) * 0.2;
			}
			break;
		case DOWN_KEY :
			if (map[(int)s->pos_y + 1][(int)s->pos_x] == '0')
			{
				s->pos_x -= cos(s->angle) * 0.2;
				s->pos_y -= -sin(s->angle) * 0.2;
			}
			break;
		case LEFT_KEY :
				s->angle += M_PI / 24;
			break;
		case RIGHT_KEY :
				s->angle -= M_PI / 24;
			break;
		case A_KEY :
			if (map[(int)s->pos_y][(int)s->pos_x] == '0')
				s->pos_x -= MOVE_SPEED;
			break;
		case B_KEY :
			if (map[(int)s->pos_y][(int)s->pos_x + 1] == '0')
				s->pos_x += MOVE_SPEED;
			break;
	}
	return (1);
}

int		move_print(t_cub *s)
{
	int x;
	int y;

	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img_ptr, 0, 0);
	draw_sqrt((int)(s->pos_x * CASE_W) - 25, (int)(s->pos_y * CASE_W) - 25, CASE_W, s->mlx_ptr, s->win_ptr, 0x777777);
	s->dir.x = cos(s->angle);
	s->dir.y = -sin(s->angle);
	
	s->plane.x = cos(s->angle - (M_PI / 2));
	s->plane.y = -sin(s->angle - (M_PI / 2));
	printf("dir %f %f plane %f %f\n", s->dir.x, s->dir.y, s->plane.x, s->plane.y);
	draw_ray(s);
	return (0);
}



void	map_converter_img(t_cub *s)
{
	int		i = 0;
	int 	j = 0;
	
	int		k = 0;
	while (k < WIN_W * WIN_H)
	{
		if (map[(k / CASE_W) / 24 / 50][(k / CASE_W) % 24] >= '1' && map[(k / CASE_W) / 24 / 50][(k / CASE_W) % 24] <= '9')
			s->data[k] = 0x000000;
		else
			s->data[k] = 0xFFFFFF;
		k++;
	}
}

int main() 
{ 
	t_cub	s;
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, WIN_W, WIN_H, "titre");
	s.pos_x = 6;
	s.pos_y = 10;
	
	s.angle = 0;
	s.img_ptr = mlx_new_image(s.mlx_ptr, WIN_W, WIN_H);
	int a = 4;
	int b = WIN_W * WIN_H;
	int c = 0;
	s.data = (int*)mlx_get_data_addr(s.img_ptr, &a, &b, &c);
	map_converter_img(&s);
	mlx_hook(s.win_ptr, KeyPress, 0, handle_press, &s);
	mlx_loop_hook(s.mlx_ptr, move_print, &s);
	mlx_loop(s.mlx_ptr);
    
    return 0; 
}  