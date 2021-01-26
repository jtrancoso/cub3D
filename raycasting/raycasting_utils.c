/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:22:59 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/26 12:24:38 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	data->img.addr[y * data->screen_width + x] = color;
}

void	sort_sprites(t_data *data)
{
	int j;
	int i;
	t_sprite tmp;

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