/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:25:56 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/03 10:50:25 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_things(t_data *data, int argc, char **argv)
{
	data->mlx = mlx_init();
	if (!read_file(data, argv[1]))
		return (0);
	if (!check_args(data, argc, argv))
		return (0);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		data->bmp.screenshot = 1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (!check_things(&data, argc, argv))
		return (0);
	if (data.bmp.screenshot != 1)
		data.win = mlx_new_window(data.mlx, data.screen_width,
		data.screen_height, "Esto no es un juego");
	data.img.img = mlx_new_image(data.mlx, data.screen_width,
	data.screen_height);
	data.img.addr = (int *)mlx_get_data_addr(data.img.img, &data.img.bpp,
	&data.img.line_len, &data.img.endian);
	if (data.bmp.screenshot != 1)
	{
		mlx_loop_hook(data.mlx, raycasting, &data);
		mlx_hook(data.win, 02, 1L << 0, press_key, &data);
		mlx_hook(data.win, 03, 1L << 1, release_key, &data);
		mlx_hook(data.win, 17, 0L, ft_close, &data);
		mlx_loop(data.mlx);
	}
	if (!create_bmp(&data))
	{
		mlx_destroy_image(data.mlx, data.img.img);
		return (handle_error(21));
	}
	return (0);
}
