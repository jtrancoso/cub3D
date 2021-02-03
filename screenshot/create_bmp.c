/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:46:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/03 10:52:03 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		set_bmpheader(t_data *data, int file_size)
{
	ft_bzero(data->bmp.bmpheader, 14);
	data->bmp.bmpheader[0] = 'B';
	data->bmp.bmpheader[1] = 'M';
	data->bmp.bmpheader[2] = (unsigned char)(file_size);
	data->bmp.bmpheader[3] = (unsigned char)(file_size >> 8);
	data->bmp.bmpheader[4] = (unsigned char)(file_size >> 16);
	data->bmp.bmpheader[5] = (unsigned char)(file_size >> 24);
	data->bmp.bmpheader[10] = 54;
}

void		set_bmpinfo(t_data *data)
{
	ft_bzero(data->bmp.bmpinfo, 40);
	data->bmp.bmpinfo[0] = 40;
	data->bmp.bmpinfo[4] = (unsigned char)(data->screen_width);
	data->bmp.bmpinfo[5] = (unsigned char)(data->screen_width >> 8);
	data->bmp.bmpinfo[6] = (unsigned char)(data->screen_width >> 16);
	data->bmp.bmpinfo[7] = (unsigned char)(data->screen_width >> 24);
	data->bmp.bmpinfo[8] = (unsigned char)(data->screen_height);
	data->bmp.bmpinfo[9] = (unsigned char)(data->screen_height >> 8);
	data->bmp.bmpinfo[10] = (unsigned char)(data->screen_height >> 16);
	data->bmp.bmpinfo[11] = (unsigned char)(data->screen_height >> 24);
	data->bmp.bmpinfo[12] = (unsigned char)1;
	data->bmp.bmpinfo[14] = (unsigned char)(data->img.bpp);
}

int			write_bmp(t_data *data, int fd, unsigned int *addr, int i)
{
	int	file_size;
	int	j;

	file_size = 54 + data->screen_width * data->screen_height *
	(data->img.bpp / 8);
	set_bmpheader(data, file_size);
	set_bmpinfo(data);
	if (!write(fd, data->bmp.bmpheader, 14))
		return (handle_error(21));
	if (!write(fd, data->bmp.bmpinfo, 40))
		return (handle_error(21));
	while (i >= 0)
	{
		j = 0;
		while (j < data->screen_width)
		{
			if (!write(fd, &addr[i * data->screen_width + j], 4))
				return (handle_error(21));
			j++;
		}
		i--;
	}
	return (1);
}

int			create_bmp(t_data *data)
{
	int				fd;
	int				i;
	unsigned int	*addr;

	fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 | O_APPEND);
	if (fd == -1)
		return (handle_error(21));
	raycasting(data);
	addr = (unsigned int *)data->img.addr;
	i = data->screen_height - 1;
	if (!write_bmp(data, fd, addr, i))
		return (handle_error(21));
	if (close(fd) == -1)
		return (handle_error(22));
	return (1);
}
