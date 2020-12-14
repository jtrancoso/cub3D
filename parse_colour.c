/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:18:25 by jtrancos          #+#    #+#             */
/*   Updated: 2020/12/14 14:19:26 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int save_colour(t_data *data, char *line, int type, int index)
{
	if (type == 1)
		data->colour.floor[index] = ft_atoi(line);
	if (type == 2)
		data->colour.sky[index] = ft_atoi(line);
}

int	valid_colour(t_data *data, char *line, int i, int type)
{
	check_colour(data, line, type);

	if (ft_isdigit(line[i]) == 0)
	{
		write(1, "Error\nInvalid colour format.\n", 29);
		return (0);
	}
	// guardar r
	save_colour(data, &line[i], type, 0);
	while (ft_isdigit(line[i]))
		i++;
	//pasar la coma
	//guardar g
	//pasar numeros
	//pasar coma
	//guardar b
	//pasar numeros
	//ver q el final esta ok (espacios o nada)
}

// ARREGLAR BIEN TODO ESTO
// save_colour -> valid_colour -> check_colour

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
		if (!valid_colour(data, &line[i], i, type))
		{
			write(1, "Error\nWrong colour bitch.\n", 26);
			return (0);
		}
		j++;
	}
}