#ifndef FILE_CONFIG_H
# define FILE_CONFIG_H

typedef struct	s_image {
	void	*img_ptr;
	int		*data;
	int		bit_pix;
	int		size_l;
	int		endian;
	int		img_h;
	int		img_w;
}				t_image;

typedef struct  s_wallTexture {
    t_image		_north;
	t_image		_south;
	t_image		_west;
	t_image		_east;
}               t_wallTexture;

typedef struct  s_backgroundColor {
    int _ceiling;
	int _floor;
}               t_backgroundColor;

typedef struct  s_map {
	char			**_tab;
	unsigned int	_width;
	unsigned int	_height;
}				t_map;

typedef struct  s_fileConfig {
    const char          *_filename;
    char                **_fileDuplicate;
    unsigned int        _resolutionWidth;
    unsigned int        _resolutionHeight;
    t_wallTexture       _wallTexture;
	t_image				_spriteTexture;
    t_backgroundColor   _backgroundColor;
	t_map				_map;
}               t_fileConfig;

#endif