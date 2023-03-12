#define mapWidth 24
#define mapHeight 24
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
#define	A_KEY 15
#define B_KEY 16
#define L_SHIFT_KEY 257
#define	MOVE_SPEED 0.1
#define ROT_SPEED 48
#define RUN_SPEED 0.2
#define FLOOR_COLOR 0x000000
#define CEILING_COLOR 0x000000

typedef	struct s_vector
{
	double	x;
	double	y;
}t_vector;

typedef struct s_key
{
	int up;
	int down;
	int left;
	int right;
	double shift;
}	t_key;

typedef struct 	s_cub
{
	double		pos_x;
	double		pos_y;
	int		start_x;
	int		start_y;
	void	*mlx_ptr2;
	void	*win_ptr2;
	void	*img_ptr2;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*data;
	int		*data2;
	char 	**map;
	double 	angle;
	t_vector	dir;
	t_vector	plane;
	t_key 		key;

}				t_cub;

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double	abs_double(double n)
{
	return (n < 0 ? n * -1 : n);
}

void	vertical_line(int x, int drawStart, int drawEnd, int color, t_cub *s)
{
	int n = x;
	while (n < WIN_H * WIN_W)
	{
		if (n / WIN_W >= drawStart && n / WIN_W <= drawEnd)
			s->data[n] = color;
		else if (n / WIN_W < drawStart)
			s->data[n] = CEILING_COLOR;
		else
			s->data[n] = FLOOR_COLOR;
		n += WIN_W;
	}
}

void raycaster(t_cub *s)
{
	double 	cameraX;
	double 	rayDirX;
	double 	rayDirY;
	int 	mapX;
	int 	mapY;
	double 	sideDistX;
	double 	sideDistY;
	double 	deltaDistX;
	double 	deltaDistY;
	double 	perpWallDist;
	int 	stepX;
	int 	stepY;
	int 	hit;
	int 	side;
	int 	lineHeight;
	int 	drawStart;
	int 	drawEnd;
	int 	color;

		for(int x = 0; x < WIN_W; x++)
		{
			
			cameraX = 2 * x / (double)(WIN_W) - 1;
			rayDirX = s->dir.x + s->plane.x * cameraX;
			rayDirY = s->dir.y + s->plane.y * cameraX;
			
			mapX = (int)(s->pos_x);
			mapY = (int)(s->pos_y);

			
			deltaDistX = abs_double(1 / rayDirX);
			deltaDistY = abs_double(1 / rayDirY);

			hit = 0; 
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (s->pos_x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - s->pos_x) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (s->pos_y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - s->pos_y) * deltaDistY;
			}
			
			while (hit == 0)
			{
			
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
			
				if (worldMap[mapX][mapY] > 0) 
					hit = 1;
			}
			
			
			if (side == 0) 
				perpWallDist = (mapX - s->pos_x + (1 - stepX) / 2) / rayDirX;
			else           
				perpWallDist = (mapY - s->pos_y + (1 - stepY) / 2) / rayDirY;

			
			lineHeight = (int)(WIN_H / perpWallDist);

			
			drawStart = -lineHeight / 2 + WIN_H / 2;
			if(drawStart < 0)
				drawStart = 0;
			
			drawEnd = lineHeight / 2 + WIN_H / 2;
			if(drawEnd >= WIN_H)
				drawEnd = WIN_H - 1;

			switch(worldMap[mapX][mapY])
			{
				case 1:  color = 0xff0000;  break; //red
				case 2:  color = 0x00ff00;  break; //green
				case 3:  color = 0x0000ff;   break; //blue
				case 4:  color = 0x66125f;  break; //white
				default: color = 0x00ffff; break; //yellow
			}
			if (side == 1) 
				color = color / 2;
			vertical_line(x, drawStart, drawEnd, color, s);
		}
}

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

void	move_key(t_cub *s)
{
	if (s->key.up)
	{
		if (worldMap[(int)(s->pos_x + s->dir.x * (MOVE_SPEED + s->key.shift))][(int)(s->pos_y)] == 0)
			s->pos_x += s->dir.x * (MOVE_SPEED + s->key.shift);
		if (worldMap[(int)(s->pos_x)][(int)(s->pos_y + s->dir.y * (MOVE_SPEED + s->key.shift))] == 0)
			s->pos_y += s->dir.y * (MOVE_SPEED + s->key.shift);
	}
	if (s->key.down)
	{
		if (worldMap[(int)(s->pos_x - s->dir.x * (MOVE_SPEED + s->key.shift))][(int)(s->pos_y)] == 0)
			s->pos_x -= s->dir.x * (MOVE_SPEED + s->key.shift);
		if (worldMap[(int)(s->pos_x)][(int)(s->pos_y - s->dir.y * (MOVE_SPEED + s->key.shift))] == 0)
			s->pos_y -= s->dir.y * (MOVE_SPEED + s->key.shift);
	}
	if (s->key.left)
		s->angle -= M_PI / ROT_SPEED;
	if (s->key.right)
		s->angle += M_PI / ROT_SPEED;
	
}

int		handle_press(int key_pressed, t_cub *s)
{
	switch(key_pressed)
	{
		case UP_KEY :
			s->key.up = 1;
			break;
		case DOWN_KEY :
			s->key.down = 1;
			break;
		case LEFT_KEY :
			s->key.left = 1;
			break;
		case RIGHT_KEY :
			s->key.right = 1;
			break;
		case L_SHIFT_KEY:
			s->key.shift = RUN_SPEED;
			break;
	}
	return (1);
}

int handle_release(int key_release, t_cub *s)
{
	switch(key_release)
	{
		case UP_KEY :
			s->key.up = 0;
			break;
		case DOWN_KEY :
			s->key.down = 0;
			break;
		case LEFT_KEY :
			s->key.left = 0;
			break;
		case RIGHT_KEY :
			s->key.right = 0;
			break;
		case L_SHIFT_KEY:
			s->key.shift = 0.0;
			break;
	}
	return (1);
}



int		move_print(t_cub *s)
{
	int x;
	int y;

	

	raycaster(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img_ptr, 0, 0);
	s->dir.x = -cos(s->angle);
	s->dir.y = sin(s->angle);
	s->plane.x = s->dir.y;
	s->plane.y = -s->dir.x;
	printf("pos %f %f dir %f %f plane %f %f angle %f\n",s->pos_x, s->pos_y, s->dir.x, s->dir.y, s->plane.x, s->plane.y, s->angle);
	move_key(s);
	return (0);
}



void	map_converter_img(t_cub *s)
{
	int		i = 0;
	int 	j = 0;
	
	int		k = 0;
	while (k < WIN_W * WIN_H)
	{
		if (worldMap[(k / CASE_W) / 24 / 50][(k / CASE_W) % 24] >= 1 && worldMap[(k / CASE_W) / 24 / 50][(k / CASE_W) % 24] <= 9)
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
	s.pos_x = 22;
	s.pos_y = 12;
	s.key.up = 0;
	s.key.down = 0;
	s.key.left = 0;
	s.key.right = 0;
	s.key.shift = 0.0;
	s.angle = 0;

	s.img_ptr = mlx_new_image(s.mlx_ptr, WIN_W, WIN_H);
	int a = 4;
	int b = WIN_W * WIN_H;
	int c = 0;
	s.data = (int*)mlx_get_data_addr(s.img_ptr, &a, &b, &c);
	//map_converter_img(&s);
	mlx_hook(s.win_ptr, KeyPress, 0, handle_press, &s);
	mlx_hook(s.win_ptr, KeyRelease, 0, handle_release, &s);
	mlx_loop_hook(s.mlx_ptr, move_print, &s);
	mlx_loop(s.mlx_ptr);
    
    return 0; 
}  
