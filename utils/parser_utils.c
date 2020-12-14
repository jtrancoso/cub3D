/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:50:02 by jtrancos          #+#    #+#             */
/*   Updated: 2020/12/11 14:06:50 by jtrancos         ###   ########.fr       */
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

//int rgb_to_hex(int r)

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
