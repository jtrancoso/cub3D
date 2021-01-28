/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:25:56 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 11:27:02 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main (int argc, char **argv)
{
	t_data data;
	
	data.mlx = mlx_init();
	if (!read_file(&data, argv[1]))
		return (0);
	/*printf("width       %d\n", data.screen_width);
	printf("height      %d\n", data.screen_height);
	printf("north       %p\n", data.textures.north.img.img);
	printf("north path  %s\n", data.textures.north.path);
	printf("south       %p\n", data.textures.south.img.img);
	printf("south path  %s\n", data.textures.south.path);
	printf("west        %p\n", data.textures.west.img.img);
	printf("west path   %s\n", data.textures.west.path);
	printf("east        %p\n", data.textures.east.img.img);
	printf("east path   %s\n", data.textures.east.path);
	printf("sprite      %p\n", data.textures.sprite.img.img);
	printf("sprite path %s\n", data.textures.sprite.path);
	printf("floor 0: %d floor 1: %d  floor 2: %d\n", data.colour.floor[0], data.colour.floor[1], data.colour.floor[2]);
	printf("sky   0: %d sky   1: %d sky   2: %d\n", data.colour.sky[0], data.colour.sky[1], data.colour.sky[2]);
	printf("map width: %d  map height: %d\n", data.map_width, data.map_height);
	printf("numsprite: %d\n", data.sprite_num);
	printf("dirx: %f diry %f planex: %f planey: %f\n", data.player.dir_x, data.player.dir_y, data.player.plane_x, data.player.plane_y);
	int i = 0;
	while (i < data.map_height)
	{
		int j = 0;
		while (j < data.map_width)
		{
			printf("%c", data.map.map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	//return (0);*/
	data.win = mlx_new_window(data.mlx, data.screen_width, data.screen_height, "raycaster");
	data.img.img = mlx_new_image(data.mlx, data.screen_width, data.screen_height);
	data.img.addr = (int *)mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx, raycasting, &data);
	mlx_hook(data.win, 02, 1L << 0, press_key, &data);
	mlx_hook(data.win, 03, 1L << 1, release_key, &data);
	mlx_hook(data.win, 17, 0L, ft_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
