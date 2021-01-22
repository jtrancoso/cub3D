/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:41:22 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/22 14:12:51 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** 1º Leemos el .cub con read
** 2º limpiamos todos los espacios
** 3º tenemos que ver que tipo de linea tenemos (text, resolucion, color, etc)
** 4º R: guardamos primer numero en anchura y segundo en altura
** 5º NSEW: guardamos la texturas 
** 6º CF: guardamos color de cielo o suelo y lo pasamos a hexa 
** 7º 012: guardamos el mapa y quitamos espacios si los hubiera
**
**
**
**
**
**
*/


int		find_texture(t_data *data, char *line)
{
	int i;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
		return(parse_texture(data, 1, &line[i]));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return(parse_texture(data, 2, &line[i]));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return(parse_texture(data, 3, &line[i]));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return(parse_texture(data, 4, &line[i]));
	else if (line[i] == 'S')
		return(parse_texture(data, 5, &line[i]));
	return (handle_error(data, 9));
}

int check_line(t_data *data, char *line)
{
	int i;

	i = 0;
	if (line[i] == '\0')
		return (1);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	else if (line[i] == 'R')
		return (parse_resolution(data, line + i));
	else if (ft_strchr("NSEW", line[i]))
		return (find_texture(data, line + i));
	else if (line[i] == 'F')
		return (parse_colour(data, 1, line + i));
	else if (line[i] == 'C')
		return (parse_colour(data, 2, line + i));
	else if (ft_strchr("012", line[i]) || ft_isspace(line[i]))
		return (map_count(data, line + i));
	return (0);
}

int	check_extension(t_data *data, const char *file, char *ext)
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
	free (tmp);
	return (handle_error(data, 1));
}

int	check_file(t_data *data, const char *file, int fd)
{
	int		ret;
	char	*line;
	int		correct_line;

	if (!check_extension(data, file, ".cub"))
		return (0);
	while ((ret = get_next_line(fd, &line) > 0))
	{
		correct_line = check_line(data, line);
		free(line);
		if (correct_line == 0)
			return (0);
	}
	correct_line = check_line(data, line);
	free (line);
	if (correct_line == 0)
		return (0);
	return (1);
}

int	check_map(t_data *data)
{
	int i;

	i = 0;
	while (i < data->map_width)
	{
		if (data->map.map[0][i] == '9' ||
			data->map.map[data->map_height - 1][i] == '9')
			return (handle_error(data, 14));
		i++;
	}
	i = 0;
	while (i < data->map_height)
	{
		if (data->map.map[i][0] == '9' ||
			data->map.map[i][data->map_width - 1] == '9')
			return (handle_error(data, 15));
		i++;
	}
	return (1);
}

int read_file(t_data *data, const char *file)
{
	int	fd;
	int	map_ok;

	init_data(data);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (handle_error(data, 0));
	if (!check_file(data, file, fd))
		return (0);
	if (close(fd) == -1)
		return (handle_error(data, 2));
	if ((fd = open(file, O_RDONLY)) == -1)
		return (handle_error(data, 0));
	if (!parse_map(data, fd))
		return (0);
	flood_fill(data, data->player.y, data->player.x, '0');
	map_ok = check_map(data);
	if (!(data->sprite = malloc(sizeof(t_sprite) * data->sprite_num)) ||
		!(data->zbuffer = malloc(sizeof(float) * data->screen_width)))
		return (0);
	convert_map(data);
	close(fd);
	return (map_ok);
}
