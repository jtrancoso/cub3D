/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:41:51 by jtrancos          #+#    #+#             */
/*   Updated: 2020/12/07 14:41:51 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_max_resolution(t_data *data)
{
	if (data->screenheight > MAX_SCREENHEIGHT)
		data->screenheight = MAX_SCREENHEIGHT;
	if (data->screenwidth > MAX_SCREENWIDTH)
		data->screenwidth = MAX_SCREENWIDTH;
}

int	parse_resolution(t_data *data, char *line)
{
	int i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
	{
		write(1, "Error. Invalid resolution.\n", 27);
		return (0);
	}
	data->screenwidth = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
	{
		write(1, "Error. Invalid resolution.\n", 27);
		return (0);
	}
	data->screenheight = ft_atoi(&line[i]);
	while (ft_idigit(line[i]))
		i++;
	if (!empty_line_end(&line[i]))
	{
		write(1, "Error\nLine not empty after resolution values.\n", 46);
		return (0);
	}
	check_max_resolution(data);
	return (1);
}
