/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 10:56:26 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/26 10:49:54 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_count(t_data *data, char *line)
{
	int line_len;

	if (!check_data(data))
		return (handle_error(data, 17));
	line_len = ft_strlen(line);
	if (data->map_width < line_len)
		data->map_width = line_len;
	data->map_height++;
	return (1);
}

int	fill_map(t_data *data, char *line, int i)
{
	int j;

	j = 0;
	while (line[j] != '\0')
	{
		if (!ft_strchr(" NSEW012", line[j]))
			return (handle_error(data, 14));
		if (line[j] == '2')
			data->sprite_num += 1;
		if (line[j] == ' ')
			data->map.map[i][j] = '0';
		else
			data->map.map[i][j] = line[j];
		j++;
	}
	if (!check_player(data, line, i))
		return (0);
	return (1);
}

int	check_map_line(t_data *data, char *line, int *i)
{
	int j;

	j = 0;
	while (ft_isspace(line[j]))
		j++;
	if (ft_isdigit(line[j]))
	{
		if (!(fill_map(data, line, *i)))
		{
			free(line);
			return (0);
		}
		*i += 1;
	}
	return (1);
}

int	alloc_map(t_data *data)
{
	int i;
	int j;

	if (!(data->map.map = malloc(data->map_height * sizeof(char *))))
		return (0);
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		if (!(data->map.map[i] = malloc(data->map_width * sizeof(char *))))
		{
			free(data->map.map);
			return (0);
		}
		while (j < data->map_width)
		{
			data->map.map[i][j] = '0';
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_map(t_data *data, int fd)
{
	char	*line;
	int		ret;
	int		i;

	if (!alloc_map(data))
		return (0);
	i = 0;
	while ((ret = get_next_line(fd, &line) > 0))
	{
		if (!check_map_line(data, line, &i))
			return (0);
		free(line);
	}
	if (!check_map_line(data, line, &i))
		return (0);
	free(line);
	if (data->player.x == -1 || data->player.y == -1)
		return (handle_error(data, 18));
	return (1);
}
