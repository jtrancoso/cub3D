/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:18:25 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/21 12:23:19 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		final_colour(t_data *data, int type)
{
	if (type == 1)
	{
		if (data->colour.floor[0] >= 0 && data->colour.floor[0] <= 255
		&& data->colour.floor[1] >= 0 && data->colour.floor[1] <= 255
		&& data->colour.floor[2] >= 0 && data->colour.floor[2] <= 255)
			return (1);
		else
			return (handle_error(data, 9));
	}
	if (type == 2)
	{
		if (data->colour.sky[0] >= 0 && data->colour.sky[0] <= 255
		&& data->colour.sky[1] >= 0 && data->colour.sky[1] <= 255
		&& data->colour.sky[2] >= 0 && data->colour.sky[2] <= 255)
			return (1);
		else
			return (handle_error(data, 9));
	}
	return (0);
}

int		check_colour(t_data *data, char *line, int type)
{
	if (type == 1)
	{
		if (data->colour.floor[0] != -1 && data->colour.floor[1] != -1
		&& data->colour.floor[2] != -1)
			return (handle_error(data, 11));
	}
	else if (type == 2)
	{
		if (data->colour.sky[0] != -1 && data->colour.sky[1] != -1
			&& data->colour.sky[2] != -1)
			return (handle_error(data, 11));
	}
	return (1);
}

void	save_colour(t_data *data, char *line, int type, int j)
{
	if (type == 1)
		data->colour.floor[j] = ft_atoi(line);
	if (type == 2)
		data->colour.sky[j] = ft_atoi(line);
}

int		valid_colour(t_data *data, char *line, int j, int type)
{
	int i;

	i = 0;
	check_colour(data, line, type);
	if (!ft_isdigit(line[i]))
		return (handle_error(data, 10));
	save_colour(data, &line[i], type, j);
	return (1);
}

int		parse_colour(t_data *data, int type, char *line)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (!ft_isspace(line[i]))
		return (handle_error(data, 10));
	while (ft_isspace(line[i]))
		i++;
	while (j < 3)
	{
		valid_colour(data, &line[i], j, type);
		while (ft_isdigit(line[i]))
			i++;
		if (j != 2 && line[i] != ',')
			return (handle_error(data, 10));
		if (j == 2 && line[i] == ',')
			return (handle_error(data, 10));
		if (line[i] == ',')
			i++;
		j++;
	}
	if (!empty_line_end(&line[i]))
		return (handle_error(data, 12));
	return (final_colour(data, type));
}
