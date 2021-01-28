/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_wall_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:11:54 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 14:00:17 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_sky_wall_floor(t_data *data, int x)
{
	int y;

	y = 0;
	while (y <= data->wall.draw_start)
	{
		my_mlx_pixel_put(data, x, y, rgb_to_hex(data->colour.sky));
		y++;
	}
	draw_texture(data, data->wall, data->ray, x);
	y = data->wall.draw_end;
	while (y <= data->screen_height)
	{
		my_mlx_pixel_put(data, x, y, rgb_to_hex(data->colour.floor));
		y++;
	}
}
