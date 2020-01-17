#include "mlx.h"
#include <stdio.h>
/*
a 0
s 1
d 2
w 13
space 49
esc 53
left 123
right 124
down 125
up 126
lcontrol 256
lcommand 259
lshift 257
rcommand 260
rcontrol 269
rshift 258


*/
int		number_of_key(int key, void *params)
{
	printf("%d\n", key);
	return (0);
}

int main()
{
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr, 100, 100, "titre");
	
	mlx_key_hook(win_ptr, number_of_key, NULL);
	mlx_loop(mlx_ptr);

}