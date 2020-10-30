#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	void	*mlx;
	void	*win;
	unsigned int rgb;
	int 	playerx;
	int		playery;
	int 	blockx;
	int		blocky;
	int		blocklen;
}				t_data;

int		ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return(0);
}

int		ft_escape(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		ft_close(data);
	}
	return(0);
}

int main (void)
{
	t_data data;
	char *relative_path = "/Users/jtrancos/Desktop/Curso/Ejercicios/cub3d/barrel.xpm";
	int img_width;
	int img_height;

	data.mlx = mlx_init();
	data.img = mlx_xpm_file_to_image(data.mlx, relative_path, &img_width, &img_height);
	data.win = mlx_new_window(data.mlx, img_height * 10, img_width * 10, "ete sech");
	printf("%i\n", img_height);
	printf("%i\n", img_width);	
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_key_hook(data.win, ft_escape, &data);
	mlx_loop(data.mlx);
}