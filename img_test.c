#include "mlx/mlx.h"

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

int main (void)
{
	t_data data;
	char *relative_path = "/Users/jtrancos/Desktop/Curso/Ejercicios/cub3d/test.xpm";
	int img_width;
	int img_height;

	data.mlx = mlx_init();
	data.img = mlx_xpm_file_to_image(data.mlx, relative_path, &img_width, &img_height);
	data.win = mlx_new_window(data.mlx, 1920, 1080, "ete sech");
	printf("%i\n", img_height);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}