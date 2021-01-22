/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:50:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/22 14:13:12 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isspace(int c)
{
	int i;

	i = 0;
	if (c == ' ' || c == '\n' || c == '\r' ||
		c == '\t' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	empty_line_end(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]))
			return(0);
		i++;
	}
	return (1);
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

void	set_player_pos(t_data *data, char nsew)
{
	if (nsew == 'N')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y= 0.66;
	}
	else if (nsew == 'S')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y= -0.66;
	}
	else if (nsew == 'E')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = 0.66;
		data->player.plane_y= 0;
	}	
	else if (nsew == 'W')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = -0.66;
		data->player.plane_y= 0;
	}
}

int		check_player(t_data *data, char *line, int y)
{
	int x;

	x = 0;
	while (line[x] != '\0')
	{
		if (ft_strchr("NSEW", line[x]))
		{
			if (data->player.x != -1 || data->player.y != -1)
				return (handle_error(data, 18));
			set_player_pos(data, line[x]);
			data->player.x = y + 0.5;
			data->player.y = x + 0.5;
			data->map.map[y][x] = '0';
		}
		x++;
	}
	return (1);
}

void	flood_fill(t_data *data, int x, int y, int prev_number)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
		return ;
	if (data->map.map[y][x] != prev_number)
		return ;
	data->map.map[y][x] = '9';
	flood_fill(data, x + 1, y, prev_number);
	flood_fill(data, x - 1, y, prev_number);
	flood_fill(data, x, y + 1, prev_number);
	flood_fill(data, x, y - 1, prev_number);
}

void	convert_map(t_data *data)
{
	int i;
	int j;
	int queonda;
	//t_sprite sprite;

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
				t_sprite sprite;
				sprite.map_x = j;
				sprite.map_y = i;
				data->sprite[queonda++] = sprite;
			}
			j++;
		}
		i++;
	}
}

/*void	create_sprite(t_data *data)
{
	t_sprite sprite;
	int i;
	int j;

	i = 0;
	while (i < data->map)
	sprite.map_x = x;
	sprite.map_y = y;
	data->sprite[data->sprite_num] = sprite;
}*/

void	init_data(t_data *data)
{
	data->screen_height = -1;
	data->screen_width = -1;
	data->map_height = 0;
	data->map_width = 0;
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
