#include "mlx/mlx.h"
#include <stdlib.h>

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
	
}

void	move(int x, int y, t_data *data)
{
	if (((unsigned int *)data->addr)[y  * 620 + x] == 0xff8000)
		return ;
	data->playerx = x;
	data->playery = y;
}

int move_player(int keycode, t_data *data)
{	
	if (keycode == 0)
		move(data->playerx - 7, data->playery, data);
	if (keycode == 1)
		move(data->playerx, data->playery + 7, data);
	if (keycode == 2)
		move(data->playerx + 7, data->playery, data);
	if (keycode == 13)
		move(data->playerx, data->playery - 7, data);
	return(0);
}

void block(t_data *data)
{
	int x, y;

	x = data->blockx;
	while (x < data->blockx + data->blocklen)
	{
		y = data->blocky;
		while (y < data->blocky + data->blocklen)
		{
			my_mlx_pixel_put(data, x, y, 0xff8000);
			y++;
		}
		x++;
	}
}

void	fill_player(t_data *data)
{
	int x, y;
	x = 0;
	while (x < 15)
	{
		y = 0;
		while (y < 15)
		{
			my_mlx_pixel_put(data, data->playerx + x - 7, data->playery + y - 7, 0x00a2e4);
			y++;
		}
		x++;
	}
}

int render(t_data *data)
{
	int y, x, i;

	
	y = 0;
	x = 0;
	i = 0;
	data->img = mlx_new_image(data->mlx, 620, 480);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
	while (y < 480)
	{
		x = 0;
		while (x < 620)
		{
			my_mlx_pixel_put(data, x, y, 0x000000);
			x++;
		}
		y++;
	}
	fill_player(data);
	block(data);
	my_mlx_pixel_put(data, data->playerx, data->playery, 0x00FF00);
	mlx_put_image_to_window(data, data->win, data->img, 0, 0);
	return (0);
}

int main (void)
{
	t_data data;

	data.blockx = 100;
	data.blocky = 125;
	data.blocklen = 200;
	data.playerx = 310;
	data.playery = 240;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 620, 480, "ete sech");
	data.rgb = 0xFF0000;
	mlx_loop_hook(data.mlx, render, &data);
	mlx_hook(data.win, 2, 0L, move_player, &data);
	mlx_key_hook(data.win, ft_escape, &data);
	mlx_loop(data.mlx);
}