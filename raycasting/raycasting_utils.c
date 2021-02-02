/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:22:59 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/01 15:48:58 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x < 0 || x >= data->screen_width || y < 0 || y >= data->screen_height)
		return ;
	data->img.addr[y * data->screen_width + x] = color;
}

void	assign_sprite(t_data *data)
{
	int i;

	i = 0;
	while (i < data->sprite_num)
	{
		data->sprite[i].dist = ((data->player.x - data->sprite[i].map_x)
		* (data->player.x - data->sprite[i].map_x) + (data->player.y -
		data->sprite[i].map_y) * (data->player.y - data->sprite[i].map_y));
		i++;
	}
}

void	sort_sprites(t_data *data)
{
	int			j;
	int			i;
	t_sprite	tmp;

	i = 0;
	while (i < data->sprite_num)
	{
		j = 0;
		while (j < data->sprite_num)
		{
			if (data->sprite[j].dist < data->sprite[i].dist)
			{
				tmp = data->sprite[j];
				data->sprite[j] = data->sprite[i];
				data->sprite[i] = tmp;
			}
			j++;
		}
		i++;
	}
}
