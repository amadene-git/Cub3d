/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:35:10 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 16:35:13 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# define BUFFER_SIZE	1
# define KEY_PRESSED	2
# define KEY_RELEASE	3
# define DESTROY_NOTIFY	17
# define UP_KEY 		122
# define DOWN_KEY 		115
# define LEFT_KEY 		113
# define RIGHT_KEY 		100
# define W_KEY 			13
# define A_KEY 			0
# define S_KEY 			1
# define D_KEY 			2
# define L_SHIFT_KEY 	257
# define ESCAPE_KEY 	65307
# define MOVE_SPEED 	0.1
# define ROT_SPEED 		150
# define RUN_SPEED 		20
# define FOV 			1

# define RESOLUTION_WIDTH_MAX	2560
# define RESOLUTION_HEIGHT_MAX	1440
# define WHITESPACE_CHARSET		" \t\r"


# include <math.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include ".libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "fileConfig.h"

typedef	struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_key
{
	int		up;
	int		down;
	int		left;
	int		right;
	int		w;
	int		a;
	int		s;
	int		d;
	double	shift;
}				t_key;

typedef struct	s_sprite
{
	double	x;
	double	y;
	double	sprite_dist;
	int		order;
}				t_sprite;

typedef struct	s_cub
{
	double		pos_x;
	double		pos_y;
	int			start_x;
	int			start_y;
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		render;
	t_image		tex1;
	t_image		tex2;
	t_image		tex3;
	t_image		tex4;
	t_image		texsprite;
	char		**map;
	double		angle;
	t_vector	dir;
	t_vector	plane;
	t_key		key;
	char		**parsing;
	char		**worldmap;
	int			res_w;
	int			res_h;
	int			ceiling;
	int			floor;
	int			mapheight;
	int			mapwidth;
	t_sprite	*sprite;
	int			save;
	t_fileConfig	_config;
}				t_cub;

typedef struct	s_raycaster
{
	int		x;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wallx;
	int		color;
	int		texx;
	int		n;
	int		texy;
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		spriteheight;
	int		drawstarty;
	int		drawendy;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;
	double	*zbuffer;
	int		d;
	int		nbr_sprite;
}				t_raycaster;

typedef struct	s_frame_saver
{
	unsigned char	*buf;
	size_t			index;
	size_t			size;
}				t_frame_saver;


// initializeBackgroundColors.c
int				initializeBackgroundColors(t_fileConfig *config);

// initializeTextures.c
int				initializeTextures(t_cub *s);
int				initializeSpriteTexture(t_cub *s);

// initializeConfigResolution.c
int				initializeConfigResolution(t_fileConfig *config);

// initializeConfig.c
char			*skipWhitespaces(char *str);
void			freeTab(char **tab);
void			printTab(char **tab);
int				checkFile(const char *filename, const char *extension);
char			**fileDuplicate(const char *filename);
int				initializeConfig(t_cub *s, const char *filename);

// check_map.c
int				initializeMap(t_cub *s);
int				init_pos(t_cub *s);

// main.c
void			takeScreenShot(t_cub *s);

// save.c
int				ft_save(char *filename, t_cub *s);

// move.c
int				handle_release(int key_release, t_cub *s);
int				handle_press(int key_pressed, t_cub *s);
void			move_key(t_cub *s);
void			move_up_down(t_cub *s);
int				mainLoop(t_cub *s);

// put_sprite,c
void			swap(t_sprite *a, t_sprite *b);
void			sprite_nbr_init(t_cub *s, t_raycaster *r);
void			sprite_pos_init(t_cub *s, t_raycaster *r);
void			sortsprites(t_sprite *sprite, int nbr_sprite);
void			sprite_init(t_cub *s, t_raycaster *r);
void			sprite_var_init(t_cub *s, t_raycaster *r);
void			put_sprite(t_cub *s, t_raycaster *r);

void			move_key(t_cub *s);
int				handle_press(int key_pressed, t_cub *s);
int				handle_release(int key_release, t_cub *s);
void			raycaster(t_cub *s);
void			raycaster_init(t_raycaster *r, t_cub *s);
void			raycaster_dda(t_raycaster *r, t_cub *s);
void			raycaster_algo(t_raycaster *r, t_cub *s);
void			raycaster(t_cub *s);


void			put_texture_n(t_raycaster *r, t_cub *s);
void			put_texture_s(t_raycaster *r, t_cub *s);
void			put_texture_e(t_raycaster *r, t_cub *s);
void			put_texture_w(t_raycaster *r, t_cub *s);
void			raycaster_init(t_raycaster *r, t_cub *s);
void			raycaster_dda(t_raycaster *r, t_cub *s);
void			raycaster_algo(t_raycaster *r, t_cub *s);
void			raycaster_texture(t_cub *s, t_raycaster *r);
void			end_of_the_world(t_cub *s, int err, char *str);
void			var_init(t_cub *s);
void			printUsage();
int				close_win(t_cub *s);
void			init_pos_utils(t_cub *s, int i, int j);

#endif
