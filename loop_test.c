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
}				t_data;

int		ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return(0);
}

int		key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		ft_close(data);
	}
	return(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int render(t_data *data)
{
	int y, x;
	
	y = 0;
	x = 0;
	data->img = mlx_new_image(data->mlx, 620, 480);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
	while (y < 480)
	{
		x = 0;
		while (x < 620)
		{
			my_mlx_pixel_put(data, x, y, data->rgb);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data, data->win, data->img, 0, 0);	
	return (0);

}

int main (void)
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 620, 480, "ete sech");
	data.rgb = 0xFFFFFF;
	mlx_loop_hook(data.mlx, render, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
}