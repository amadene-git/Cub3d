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
#include <libc.h>
#include <math.h>
#define CASE_W 50
#define WIN_H 1200
#define WIN_W 1200
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
	void	*tex_ptr;
	int		*data;
	char 	**map;
	double 	angle;
	t_vector	dir;
	t_vector	plane;

}				t_cub;

int main() 
{ 
	t_cub	s;
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, WIN_W, WIN_H, "titre");
	int width;
	int height;
	s.tex_ptr = mlx_xpm_file_to_image(s.mlx_ptr, "texture.xpm", &width, &height);
	printf("wesh\n");
	mlx_put_image_to_window(s.mlx_ptr, s.win_ptr, s.tex_ptr, 0, 0);
	mlx_loop(s.mlx_ptr);
    
    return 0; 
}  