/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:50:02 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/26 12:15:46 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_isspace(int c)
{
	int i;

	i = 0;
	if (c == ' ' || c == '\n' || c == '\r' ||
		c == '\t' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int		check_extension(t_data *data, const char *file, char *ext)
{
	size_t	len;
	size_t	ext_len;
	char	*tmp;

	len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (handle_error(data, 1));
	tmp = ft_substr(file, len - ext_len, ext_len);
	if (ft_strncmp(tmp, ext, 4) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (handle_error(data, 1));
}

int		empty_line_end(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	set_player_pos(t_data *data, char nsew)
{
	if (nsew == 'S')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
	else if (nsew == 'E')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (nsew == 'W')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
}

int		check_player(t_data *data, char *line, int y)
{
	int x;

	x = 0;
	while (line[x] != '\0')
	{
		if (ft_strchr("NSEW", line[x]))
		{
			if (data->player.x != -1 || data->player.y != -1)
				return (handle_error(data, 19));
			if (line[x] == 'N')
			{
				data->player.dir_x = -1;
				data->player.dir_y = 0;
				data->player.plane_x = 0;
				data->player.plane_y = 0.66;
			}
			else
				set_player_pos(data, line[x]);
			data->player.x = y + 0.5;
			data->player.y = x + 0.5;
			data->map.map[y][x] = '0';
		}
		x++;
	}
	return (1);
}
