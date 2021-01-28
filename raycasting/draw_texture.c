/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:21:07 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 11:26:05 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_texture(t_data *data, t_wall wall, t_ray ray, int x)
{
	float			step;
	float			tex_pos;
	int				tex_y;
	int				y;
	unsigned int	color;

	step = 1.0 * wall.texture.height / ray.line_height;
	tex_pos = (wall.draw_start - data->screen_height / 2 +
	ray.line_height / 2) * step;
	y = wall.draw_start;
	while (y < wall.draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = ((unsigned int *)wall.texture.img.addr)[wall.texture.width
		* tex_y + wall.texture_x];
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
		tex_x = wall.texture.width - tex_x - 1;
	if (ray.side == 1 && ray.dir_y < 0)
		tex_x = wall.texture.width - tex_x - 1;
	wall.texture_x = tex_x;
	put_texture(data, wall, ray, x);
}
