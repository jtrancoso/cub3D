/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:18:25 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/03 10:49:25 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		final_colour(t_data *data, int type)
{
	if (type == 1)
	{
		if (data->colour.floor[0] >= 0 && data->colour.floor[0] <= 255
		&& data->colour.floor[1] >= 0 && data->colour.floor[1] <= 255
		&& data->colour.floor[2] >= 0 && data->colour.floor[2] <= 255)
			return (1);
		else
			return (handle_error(10));
	}
	if (type == 2)
	{
		if (data->colour.sky[0] >= 0 && data->colour.sky[0] <= 255
		&& data->colour.sky[1] >= 0 && data->colour.sky[1] <= 255
		&& data->colour.sky[2] >= 0 && data->colour.sky[2] <= 255)
			return (1);
		else
			return (handle_error(10));
	}
	return (0);
}

int		check_colour(t_data *data, int type)
{
	if (type == 1)
	{
		if (data->colour.floor[0] != -1 && data->colour.floor[1] != -1
		&& data->colour.floor[2] != -1)
			return (handle_error(12));
	}
	else if (type == 2)
	{
		if (data->colour.sky[0] != -1 && data->colour.sky[1] != -1
			&& data->colour.sky[2] != -1)
			return (handle_error(12));
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
	if (!check_colour(data, type))
		return (0);
	if (!ft_isdigit(line[i]))
		return (handle_error(11));
	save_colour(data, &line[i], type, j);
	return (1);
}

int		parse_colour(t_data *data, int type, char *line, int i)
{
	int j;

	i = 1;
	j = 0;
	if (!ft_isspace(line[i]))
		return (handle_error(11));
	while (ft_isspace(line[i]))
		i++;
	while (j < 3)
	{
		if (!valid_colour(data, &line[i], j, type))
			return (0);
		while (ft_isdigit(line[i]))
			i++;
		if (j != 2 && line[i] != ',')
			return (handle_error(11));
		if (j == 2 && line[i] == ',')
			return (handle_error(11));
		if (line[i] == ',')
			i++;
		j++;
	}
	if (!empty_line_end(&line[i]))
		return (handle_error(13));
	return (final_colour(data, type));
}
