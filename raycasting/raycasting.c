/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:49:09 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 11:22:55 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_walls_side(t_data *data, int x)
{
	if (data->ray.side == 0)
		data->ray.perpwalldist = (data->ray.map_x - data->player.x +
		(1 - data->ray.step_x) / 2) / data->ray.dir_x;
	else
		data->ray.perpwalldist = (data->ray.map_y - data->player.y +
		(1 - data->ray.step_y) / 2) / data->ray.dir_y;
	if (data->ray.side == 0)
		data->wall.texture = (data->ray.step_x == -1) ? data->textures.east
		: data->textures.west;
	else
		data->wall.texture = (data->ray.step_y == -1) ? data->textures.south
		: data->textures.north;
	data->ray.line_height = (int)(data->screen_height /
	data->ray.perpwalldist);
	data->wall.draw_start = -data->ray.line_height / 2 +
	data->screen_height / 2;
	if (data->wall.draw_start < 0)
		data->wall.draw_start = 0;
	data->wall.draw_end = data->ray.line_height / 2 +
	data->screen_height / 2;
	if (data->wall.draw_end >= data->screen_height)
		data->wall.draw_end = data->screen_height - 1;
}

void	find_walls(t_data *data, int x)
{
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
		if (data->map.map[data->ray.map_x][data->ray.map_y] == '1')
			data->ray.hit = 1;
	}
}

void	calculate_steps(t_data *data, int x)
{
	if (data->ray.dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.x - data->ray.map_x) *
		data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.x) *
		data->ray.delta_dist_x;
	}
	if (data->ray.dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.y - data->ray.map_y) *
		data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.y) *
		data->ray.delta_dist_y;
	}
}

void	set_raycasting(t_data *data, int x)
{
	data->ray.camera_x = 2 * x / (float)data->screen_width - 1;
	data->ray.dir_x = data->player.dir_x + data->player.plane_x *
	data->ray.camera_x;
	data->ray.dir_y = data->player.dir_y + data->player.plane_y *
	data->ray.camera_x;
	data->ray.map_x = (int)data->player.x;
	data->ray.map_y = (int)data->player.y;
	data->ray.hit = 0;
	if (data->ray.dir_y == 0)
		data->ray.delta_dist_x = 0;
	else
		data->ray.delta_dist_x = data->ray.dir_x == 0 ? 1 :
		fabs(1 / data->ray.dir_x);
	if (data->ray.dir_x == 0)
		data->ray.delta_dist_y = 0;
	else
		data->ray.delta_dist_y = data->ray.dir_y == 0 ? 1 :
		fabs(1 / data->ray.dir_y);
}

int		raycasting(t_data *data)
{
	int x;
	int color;
	int tex_y;

	x = 0;
	move_player(data);
	while (x < data->screen_width)
	{
		set_raycasting(data, x);
		calculate_steps(data, x);
		find_walls(data, x);
		set_walls_side(data, x);
		print_sky_wall_floor(data, x);
		data->zbuffer[x] = data->ray.perpwalldist;
		x++;
	}
	assign_sprite(data);
	sort_sprites(data);
	draw_sprite(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
