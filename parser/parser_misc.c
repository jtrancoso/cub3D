/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:08:23 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/03 10:33:59 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data(t_data *data)
{
	data->bmp.screenshot = 0;
	data->screen_height = -1;
	data->screen_width = -1;
	data->map_height = 0;
	data->map_width = 0;
	data->map.inmap = 0;
	data->textures.east.height = -1;
	data->textures.north.height = -1;
	data->textures.south.height = -1;
	data->textures.west.height = -1;
	data->textures.sprite.height = -1;
	data->player.x = -1;
	data->player.y = -1;
	data->sprite_num = 0;
	data->colour.floor[0] = -1;
	data->colour.floor[1] = -1;
	data->colour.floor[2] = -1;
	data->colour.sky[0] = -1;
	data->colour.sky[1] = -1;
	data->colour.sky[2] = -1;
}

void	flood_fill(t_data *data, int x, int y, int prev_number)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
		return ;
	if (data->map.map[y][x] != prev_number)
		return ;
	ft_isdigit(data->screen_height);
	data->map.map[y][x] = '9';
	flood_fill(data, x + 1, y, prev_number);
	flood_fill(data, x - 1, y, prev_number);
	flood_fill(data, x, y + 1, prev_number);
	flood_fill(data, x, y - 1, prev_number);
}

int		check_data(t_data *data)
{
	if (data->screen_height == -1 || data->screen_width == -1 ||
	data->textures.east.height == -1 || data->textures.north.height == -1 ||
	data->textures.south.height == -1 || data->textures.west.height == -1 ||
	data->textures.sprite.height == -1 || data->colour.floor[0] == -1 ||
	data->colour.floor[1] == -1 || data->colour.floor[2] == -1 ||
	data->colour.sky[0] == -1 || data->colour.sky[1] == -1 ||
	data->colour.sky[2] == -1)
		return (0);
	return (1);
}

void	convert_map(t_data *data)
{
	int			i;
	int			j;
	int			queonda;
	t_sprite	sprite;

	i = 0;
	queonda = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map.map[i][j] == '9')
				data->map.map[i][j] = '0';
			if (data->map.map[i][j] == '2')
			{
				sprite.map_x = i + 0.5;
				sprite.map_y = j + 0.5;
				data->sprite[queonda++] = sprite;
			}
			j++;
		}
		i++;
	}
}
