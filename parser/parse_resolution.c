/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:17:59 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/04 12:04:43 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_max_resolution(t_data *data)
{
	if (data->screen_height > MAX_SCREENHEIGHT || data->screen_height == -1)
		data->screen_height = MAX_SCREENHEIGHT;
	if (data->screen_width > MAX_SCREENWIDTH || data->screen_width == -1)
		data->screen_width = MAX_SCREENWIDTH;
}

int		check_if_zero(t_data *data)
{
	if (data->screen_height == 0 || data->screen_width == 0)
		return (0);
	else
		return (1);
}

int		check_checkings(t_data *data, char *line, int i)
{
	if (!empty_line_end(&line[i]))
		return (handle_error(4));
	if (!check_if_zero(data))
		return (handle_error(3));
	check_max_resolution(data);
	return (1);
}

int		parse_resolution(t_data *data, char *line)
{
	int i;

	i = 1;
	if (!ft_isspace(line[i]))
		return (handle_error(3));
	while (ft_isspace(line[i]))
		i++;
	if (ft_isdigit(line[i]) == 0)
		return (handle_error(3));
	if (data->screen_height != -2 || data->screen_width != -2)
		return (handle_error(25));
	data->screen_width = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
		return (handle_error(3));
	data->screen_height = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	if (!check_checkings(data, line, i))
		return (0);
	return (1);
}
