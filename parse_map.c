/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 10:56:26 by jtrancos          #+#    #+#             */
/*   Updated: 2020/12/16 13:15:45 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_count(t_data *data, char *line)
{
	int line_len;

	if (!check_data(data))
	{
		write(1, "Error\nMap is not the last element of the file.\n", 47);
		return (0);
	}
	line_len = ft_strlen(line);
	if (data->map_width < line_len)
		data->map_width = line_len;
	data->map_height++;
	return (1);
}