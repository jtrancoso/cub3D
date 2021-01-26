/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:17:59 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/26 10:49:51 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_max_resolution(t_data *data)
{
	if (data->screen_height > MAX_SCREENHEIGHT)
		data->screen_height = MAX_SCREENHEIGHT;
	if (data->screen_width > MAX_SCREENWIDTH)
		data->screen_width = MAX_SCREENWIDTH;
}

int		parse_resolution(t_data *data, char *line)
{
	int i;

	i = 1;
	if (!ft_isspace(line[i]))
		return (handle_error(data, 3));
	while (ft_isspace(line[i]))
		i++;
	if (ft_isdigit(line[i]) == 0)
		return (handle_error(data, 3));
	data->screen_width = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
		return (handle_error(data, 3));
	data->screen_height = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	if (!empty_line_end(&line[i]))
		return (handle_error(data, 4));
	check_max_resolution(data);
	return (1);
}
