#include "mlx/mlx.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
	int		x, y;
	void	*mlx;
	void	*mlx_win;
	unsigned int r  = 0xBE0032;
	unsigned int o  = 0xFFA500;
	unsigned int ye  = 0xFFE900;
	unsigned int g  = 0x00FF00;
	unsigned int b  = 0x0000FF;
	unsigned int b2 = 0x2B3D68;
	unsigned int p  = 0x7F00FF;
	t_data	img;

	x = 0;
	y = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "ete sech");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	while (y < 1080)
	{
		x = 0;	
		while (x < 1920)
		{
			if (x < 275)
			{
				my_mlx_pixel_put(&img, x, y, r);
				r++;
			}
			if (x >= 275 && x < 550)
			{
				my_mlx_pixel_put(&img, x, y, o);
				o++;
			}
			if (x >= 550 && x < 825)
			{
				my_mlx_pixel_put(&img, x, y, ye);
				ye++;
			}
			if (x >= 825 && x < 1100)
			{
				my_mlx_pixel_put(&img, x, y, g);
				g++;
			}
			if (x >= 1100 && x < 1375)
			{
				my_mlx_pixel_put(&img, x, y, b);
				//b++;
			}
			if (x >= 1375 && x < 1650)
			{
				my_mlx_pixel_put(&img, x, y, b2);
			//	b2++;
			}
			if (x >= 1650 && x < 1920)
			{
				my_mlx_pixel_put(&img, x, y, p);
			//	p++;
			}
			x++;
		}
		y++;
		r  = 0xBE0032;
		o  = 0xFFA500;
		ye  = 0xFFE900;
		g  = 0x00FF00;
		b  = 0x0000FF;
		b2 = 0x2B3D68;
		p  = 0x7F00FF;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

}