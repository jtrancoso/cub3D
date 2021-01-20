/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:19:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/20 21:40:06 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_texture_init(t_data *data, int type)
{
	if (type == 1)
		return (data->textures.north.height == -1 ? 1 : 0);
	else if (type == 2)
		return (data->textures.south.height == -1 ? 1 : 0);
	else if (type == 3)
		return (data->textures.west.height == -1 ? 1 : 0);
	else if (type == 4)
		return (data->textures.east.height == -1 ? 1 : 0);
	else if (type == 5)
		return (data->textures.sprite.height == -1 ? 1 : 0);
	return (1);
}

int	get_texture_path(t_data *data, int type, char *line)
{
	if (!check_texture_init(data, type))
		return (handle_error(data, 6));
	if (type == 1)
		data->textures.north.path = ft_strtrim(line, " ");
	else if (type == 2)
		data->textures.south.path = ft_strtrim(line, " ");
	else if (type == 3)
		data->textures.west.path = ft_strtrim(line, " ");
	else if (type == 4)
		data->textures.east.path = ft_strtrim(line, " ");
	else if (type == 5)
		data->textures.sprite.path = ft_strtrim(line, " ");
	return (1);
}

int		get_texture(t_data *data, t_texture *texture, char *path)
{
	int fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		close(fd);
		return (handle_error(data, 8));
	}
	texture->img.img = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	if (!texture->img.img)
		return (handle_error(data, 7));
	if (!(texture->img.addr = (int *)mlx_get_data_addr(texture->img.img, &texture->img.bpp, &texture->img.line_len, &texture->img.endian)))
		return (0);
//	printf("tw: %d, th: %d, img: %p, bpp: %d, linelen: %d, endian: %d\n", texture->width, texture->height, texture->img.img, texture->img.bpp, texture->img.line_len, texture->img.endian);
	//printf("%x\n", ((unsigned int)data->wall.texture.img.addr[0]));
	return (1);
}

int	assign_texture(t_data *data, int type)
{
	if (type == 1)
		return (get_texture(data, &data->textures.north, data->textures.north.path));
	else if (type == 2)
		return (get_texture(data, &data->textures.south, data->textures.south.path));
	else if (type == 3)
		return (get_texture(data, &data->textures.west, data->textures.west.path));
	else if (type == 4)
		return (get_texture(data, &data->textures.east, data->textures.east.path));
	else if (type == 5)
		return (get_texture(data, &data->textures.sprite, data->textures.sprite.path));
	return (0);
}

int	parse_texture(t_data *data, int type, char *line)
{
	int i;
	if (type == 5)
		i = 1;
	else
		i = 2;
	if (!ft_isspace(line[i]))
		return (handle_error(data, 5));
	while (ft_isspace(line[i]))
		i++;
	if (!ft_isascii(line[i]))
		return (handle_error(data, 5));
	if (!get_texture_path(data, type, &line[i]))
		return (0);
	if (!assign_texture(data, type))
		return (0);
	return (1);
}