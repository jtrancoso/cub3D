/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:18:25 by jtrancos          #+#    #+#             */
/*   Updated: 2020/12/15 12:26:42 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		final_colour(t_data *data, int type)
{
	if (type == 1)
	{
		if (data->colour.floor[0] >= 0 && data->colour.floor[0] <= 255 && data->colour.floor[1] >= 0 && data->colour.floor[1] <= 255 && data->colour.floor[2] >= 0 && data->colour.floor[2] <= 255)
			return (1);
		else
		{
			write(1, "Error\nInvalid colour\n", 21);
			return (0);
		}
	}
	if (type == 2)
	{
		if (data->colour.sky[0] >= 0 && data->colour.sky[0] <= 255 && data->colour.sky[1] >= 0 && data->colour.sky[1] <= 255 && data->colour.sky[2] >= 0 && data->colour.sky[2] <= 255)
			return (1);
		else
		{
			write(1, "Error\nInvalid colour\n", 21);
			return (0);
		}
	}
	return (0);
}

int	check_colour(t_data *data, char *line, int type)
{
	if (type == 1)
	{
		if (data->colour.floor[0] != -1 && data->colour.floor[1] != -1
		&& data->colour.floor[2] != -1)
		{
			write (1, "Error\nDuplicated colour\n.", 25);
			return (0);
		}
	}
	else if (type == 2)
	{
		if (data->colour.sky[0] != -1 && data->colour.sky[1] != -1
			&& data->colour.sky[2] != -1)
		{
			write (1, "Error\nDuplicated colour\n.", 25);
			return (0);
		}
	}
	return (1);
}

void save_colour(t_data *data, char *line, int type, int j)
{
	if (type == 1)
		data->colour.floor[j] = ft_atoi(line);
	if (type == 2)
		data->colour.sky[j] = ft_atoi(line);
}

int	valid_colour(t_data *data, char *line, int j, int type)
{
	int i;

	i = 0;
	check_colour(data, line, type);
	if (!ft_isdigit(line[i]))
	{
		write(1, "Error\nInvalid colour format.\n", 29);
		return (0);
	}
	save_colour(data, &line[i], type, j);
	return (1);
}

int	parse_colour(t_data *data, int type, char *line)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (!ft_isspace(line[i]))
	{
		write(1, "Error\nInvalid colour format.\n", 29);
		return (0);
	}
	while (ft_isspace(line[i]))
		i++;
	while (j < 3)
	{
		valid_colour(data, &line[i], j, type);
		while (ft_isdigit(line[i]))
			i++;
		if (j != 2 && line[i] != ',')
		{
			write(1, "Error\nInvalid colour format.\n", 29);
			return (0);
		}
		if (line[i] == ',')
			i++;
		j++;
	}
	if (!empty_line_end(&line[i]))
	{
		write(1, "Error\nLine not empty after colour values.\n", 42);
		return (0);
	}
	return (final_colour(data, type));
}