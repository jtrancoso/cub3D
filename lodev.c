#include "mlx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define mapwidth 24
#define mapheight 24
#define screenwidth 1920
#define screenheight 1080

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	time;
	float	old_time;

}				t_player;

/*typedef struct	s_map
{
	;
}				t_map;*/

/*typedef struct	s_rgb
{
	int		r;
	int		g;
	int		b;
}				t_rgb;*/

typedef struct	s_ray
{
	float	camera_x;
	float	dir_x;
	float	dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perpwalldist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
}				t_ray;

typedef struct	s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_texture
{
	int		width;
	int		height;
	char	*path;
	t_img	img;
}				t_texture;

typedef struct	s_textures
{
	t_texture	sprite;
	t_texture	north;
	t_texture	east;
	t_texture	south;
	t_texture	west;
}				t_textures;

typedef struct s_wall
{
	t_texture	texture;
	int			texture_x;
	int			x;
	float			draw_start;
	float			draw_end;
}				t_wall;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	unsigned int rgb;
	int 	blockx;
	int		blocky;
	int		blocklen;
	int		width;
	int		height;
	t_player	player;
	t_ray		ray;
	t_img		img;
	t_wall		wall;
	t_textures	textures;
	//t_map		map;
	//t_rgb		rgb;
	
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

int worldmap [mapwidth][mapheight] = {
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4},
  {4,0,1,0,0,0,0,5,5,5,5,5,5,5,5,5,4,4,0,4,4,4,4,4},
  {4,0,1,0,0,0,0,5,0,5,0,5,0,5,0,5,4,0,0,0,4,4,4,1},
  {4,0,4,0,0,0,0,5,0,0,0,0,0,0,0,5,4,0,0,0,0,0,0,4},
  {4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,1},
  {4,0,4,0,0,0,0,5,0,0,0,0,0,0,0,5,4,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,4,0,0,0,4,4,4,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,4,4,4,4,4,4,4,1},
  {4,4,4,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,4,4,4,4,4,0,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4},
  {4,4,4,4,4,4,0,4,4,4,4,0,4,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,4,0,4,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,4,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,4,0,4,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,4,0,4,0,0,0,0,4,4,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,4,0,4,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,4,0,4,0,0,0,0,4,4,0,4,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,4,0,4,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	data->img.addr[y * screenwidth + x] = color;
}

int		get_texture(t_data *data, t_texture *texture, char *path)
{
	int fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		printf("hola\n");
		close(fd);
		return (0);
	}
	texture->img.img = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	if (!texture->img.img)
	{
		printf("There is something wrong with your texture\n");
		return (0);
	}
	if (!(texture->img.addr = (int *)mlx_get_data_addr(texture->img.img, &texture->img.bpp, &texture->img.line_len, &texture->img.endian)))
		return (0);
//	printf("tw: %d, th: %d, img: %p, bpp: %d, linelen: %d, endian: %d\n", texture->width, texture->height, texture->img.img, texture->img.bpp, texture->img.line_len, texture->img.endian);
	//printf("%x\n", ((unsigned int)data->wall.texture.img.addr[0]));
	return (1);
}
void	put_texture(t_data *data, t_wall wall, t_ray ray, int x)
{
	float	step;
	float	tex_pos;
	int		tex_y;
	int		y;
	unsigned int color;
	
	step = 1.0 * wall.texture.height / ray.line_height;
	//printf("th: %d, lh: %d, ds: %f, step: %f, tex_pos: %f, tex_y: %d, y: %d\n", wall.texture.height, ray.line_height, wall.draw_start, step, tex_pos, tex_y, y);
	tex_pos = (wall.draw_start - screenheight / 2 + ray.line_height / 2) * step;
	//printf("th: %d, lh: %d, ds: %f, step: %f, tex_pos: %f, tex_y: %d, y: %d\n", wall.texture.height, ray.line_height, wall.draw_start, step, tex_pos, tex_y, y);
	y = wall.draw_start;
	while (y < wall.draw_end)
	{
		//printf("th: %d, lh: %d, ds: %f, step: %f, tex_pos: %f, tex_y: %d, y: %d\n", wall.texture.height, ray.line_height, wall.draw_start, step, tex_pos, tex_y, y);
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = ((unsigned int *)wall.texture.img.addr)[wall.texture.width * tex_y + wall.texture_x];
		//if (data->ray.side == 1 && worldmap[data->ray.map_x][data->ray.map_y] != 4 )
		//	color /= 2;
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}
void	draw_texture(t_data *data, t_wall wall, t_ray ray, int x)
{
	float	wall_x;
	int		tex_x;

	if (ray.side == 0)
		wall_x = data->player.y + ray.perpwalldist * ray.dir_y;
	else
		wall_x = data->player.x + ray.perpwalldist * ray.dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)wall.texture.width);
	if (ray.side == 0 && ray.dir_x > 0)
		tex_x = wall.texture.width	- tex_x - 1;
	if (ray.side == 1 && ray.dir_y < 0)
		tex_x = wall.texture.width - tex_x - 1;
	wall.texture_x = tex_x;
	put_texture(data, wall, ray, x);
}

int move_player(int keycode, t_data *data)
{
	float move_speed = 0.4;
	float rot_speed = 0.1;
	if (keycode == 13) //forward
	{
		if(worldmap[(int)(data->player.x + data->player.dir_x * move_speed)][(int)(data->player.y)] == 0)
			data->player.x += data->player.dir_x * move_speed;
		if(worldmap[(int)(data->player.x)][(int)(data->player.y + data->player.dir_y * move_speed)] == 0)
			data->player.y += data->player.dir_y * move_speed;
	}
	if (keycode == 1) //back
	{
		if(worldmap[(int)(data->player.x - data->player.dir_x * move_speed)][(int)(data->player.y)] == 0) 
			data->player.x -= data->player.dir_x * move_speed;
		if(worldmap[(int)(data->player.x)][(int)(data->player.y - data->player.dir_y * move_speed)] == 0)
			data->player.y -= data->player.dir_y * move_speed;
	}

	if (keycode == 2) //right
	{
		if(worldmap[(int)(data->player.x + data->player.dir_y * move_speed)][(int)(data->player.y)] == 0) 
			data->player.x += data->player.dir_y * move_speed;
		if(worldmap[(int)(data->player.x)][(int)(data->player.y - data->player.dir_x * move_speed)] == 0)
			data->player.y -= data->player.dir_x * move_speed;
	}
	if (keycode == 0) //left
	{
		if(worldmap[(int)(data->player.x - data->player.dir_y * move_speed)][(int)(data->player.y)] == 0) 
			data->player.x -= data->player.dir_y * move_speed;
		if(worldmap[(int)(data->player.x)][(int)(data->player.y + data->player.dir_x * move_speed)] == 0)
			data->player.y += data->player.dir_x * move_speed;
	}
	if (keycode == 123) //left rot
	{
		float old_dir_x = data->player.dir_x;
		float old_plane_x = data->player.plane_x;
		data->player.dir_x = data->player.dir_x * cos(rot_speed) - data->player.dir_y * sin(rot_speed);
		data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y * cos(rot_speed);
		data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
		data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
	}
	if (keycode == 124) //right rot
	{
		float old_dir_x = data->player.dir_x;
		float old_plane_x = data->player.plane_x;
		data->player.dir_x = data->player.dir_x * cos(-rot_speed) - data->player.dir_y * sin(-rot_speed);
		data->player.dir_y = old_dir_x * sin(-rot_speed) + data->player.dir_y * cos(-rot_speed);
		data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
		data->player.plane_y = old_plane_x * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
	}
	return (0);
}

int raycasting(t_data *data)
{
	int x = 0;
	int color;
	int tex_y;

	while (x < screenwidth)
	{
		data->ray.camera_x = 2 * x / (float)screenwidth - 1;
		data->ray.dir_x = data->player.dir_x + data->player.plane_x * data->ray.camera_x;
		data->ray.dir_y = data->player.dir_y + data->player.plane_y * data->ray.camera_x;
		data->ray.map_x = (int)data->player.x;
		data->ray.map_y = (int)data->player.y;
		data->ray.delta_dist_x = data->ray.dir_y == 0 ? 1 : fabs(1 / data->ray.dir_x);
		data->ray.delta_dist_y = data->ray.dir_x == 0 ? 1 : fabs(1 / data->ray.dir_y);
		data->ray.hit = 0;

		if (data->ray.dir_x < 0)
		{
			data->ray.step_x = -1;
			data->ray.side_dist_x = (data->player.x - data->ray.map_x) * data->ray.delta_dist_x;
		}
		else
		{
			data->ray.step_x = 1;
			data->ray.side_dist_x = (data->ray.map_x + 1 - data->player.x) * data->ray.delta_dist_x;
		}
		if (data->ray.dir_y < 0)
		{
			data->ray.step_y = -1;
			data->ray.side_dist_y = (data->player.y - data->ray.map_y) * data->ray.delta_dist_y;
		}
		else
		{
			data->ray.step_y = 1;
			data->ray.side_dist_y = (data->ray.map_y + 1 - data->player.y) * data->ray.delta_dist_y;
		}
		while (data->ray.hit == 0)
		{
			if (data->ray.side_dist_x < data->ray.side_dist_y)
			{
				data->ray.side_dist_x += data->ray.delta_dist_x;
				data->ray.map_x += data->ray.step_x;
				data->ray.side = 0;
			}
			else
			{
				data->ray.side_dist_y += data->ray.delta_dist_y;
				data->ray.map_y += data->ray.step_y;
				data->ray.side = 1;
			}
			if (worldmap[data->ray.map_x][data->ray.map_y] > 0)
				data->ray.hit = 1;
		}
		//calculate sides
		if (data->ray.side == 0)
			data->ray.perpwalldist = (data->ray.map_x - data->player.x + (1 - data->ray.step_x) / 2) / data->ray.dir_x;
		else
			data->ray.perpwalldist = (data->ray.map_y - data->player.y + (1 - data->ray.step_y) / 2) / data->ray.dir_y;
		if (data->ray.side == 0)
			data->wall.texture = (data->ray.step_x == -1) ? data->textures.east : data->textures.west;
		else
			data->wall.texture = (data->ray.step_y == -1) ? data->textures.south : data->textures.north;
		data->ray.line_height = (int)(screenheight / data->ray.perpwalldist);
		data->wall.draw_start = -data->ray.line_height / 2 + screenheight / 2;
		if (data->wall.draw_start < 0)
			data->wall.draw_start = 0;
		data->wall.draw_end = data->ray.line_height / 2 + screenheight / 2;
		if (data->wall.draw_end >= screenheight)
			data->wall.draw_end = screenheight - 1;

		//suelo y cielo y textura
		int y = 0;
		while (y < data->wall.draw_start)
		{
			my_mlx_pixel_put(data, x, y, 0x44ceeb);
			y++;
		}
		draw_texture(data, data->wall, data->ray, x);
		y = data->wall.draw_end;
		while (y < screenheight)
		{
			my_mlx_pixel_put(data, x, y, 0x595959);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int main (int argc, char **argv)
{
	t_data data;
	data.width = 640;
	data.player.x = 10;
	data.player.y = 5;
	data.player.dir_x = -1;
	data.player.dir_y = 0;
	data.player.plane_x = 0;
	data.player.plane_y= 0.66;
	data.player.time = 0;
	data.player.old_time = 0;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, screenwidth, screenheight, "raycaster");
	data.img.img = mlx_new_image(data.mlx, screenwidth, screenheight);
	data.img.addr = (int *)mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	get_texture(&data, &data.textures.east, "/Users/jtrancos/Desktop/Curso/Ejercicios/cub3d/textures/eagle.xpm");
	get_texture(&data, &data.textures.south, "/Users/jtrancos/Desktop/Curso/Ejercicios/cub3d/textures/mossy.xpm");
	get_texture(&data, &data.textures.west, "/Users/jtrancos/Desktop/Curso/Ejercicios/cub3d/textures/greystone.xpm");
	get_texture(&data, &data.textures.north, "/Users/jtrancos/Desktop/Curso/Ejercicios/cub3d/textures/bluestone.xpm");	
	mlx_loop_hook(data.mlx, raycasting, &data);
	mlx_hook(data.win, 2, 0L, move_player, &data);
	mlx_key_hook(data.win, ft_escape, &data);
	mlx_loop(data.mlx);
}