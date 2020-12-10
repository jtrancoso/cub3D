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
	{
		write(1, "Error\nDuplicated texture.\n", 26);
		return (0);
	}
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
		return (0);
	}
	texture->img.img = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	if (!texture->img.img)
	{
		printf("There is something wrong with your texture\n");
		return (0);
	}
	if (!(texture->img.addr = (int *)mlx_get_data_addr(texture->img.img, &texture->img.bpp, &texture->img.line_len, &texture->img.endian)))
		return (0);
//	printf("tw: %d, th: %d, img: %p, bpp: %d, linelen: %d, endian: %d\n", texture->width, texture->height, texture->img.img, texture->img.bpp, texture->img.line_len, texture->img.endian);
	//printf("%x\n", ((unsigned int)data->wall.texture.img.addr[0]));
	return (1);
}

// FALTA EL GET_TEXTUTE_TYPE

int	parse_texture(t_data *data, int type, char *line)
{
	int i;
	if (type == 5)
		i = 1;
	else
		i = 2;
	if (!ft_isspace(line[i]))
	{
		write(1, "Error\nWrong texture path.\n", 26);
		return (0);
	}
	while (ft_isspace(line[i]))
		i++;
	if (!ft_isascii(line[i]))
	{
		write(1, "Error\nWrong texture path.\n", 26);
		return (0);
	}
	get_texture_path(data, type, &line[i]);
	return (1);
}