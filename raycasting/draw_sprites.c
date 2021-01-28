/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:09:53 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/27 13:48:13 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_sprite(t_data *data, int i, int stp, int y)
{
	while (y < data->sprite[i].drawend_y)
	{
		data->sprite[i].d = (y) * 256 - data->screen_height
		* 128 + data->sprite[i].sprite_h * 128;
		data->sprite[i].tex_y = ((data->sprite[i].d *
		data->textures.sprite.height) /
		data->sprite[i].sprite_h) / 256;
		data->sprite[i].color =
		((unsigned int*)data->textures.sprite.img.addr)
		[data->textures.sprite.width * data->sprite[i].tex_y +
		data->sprite[i].tex_x];
		if ((data->sprite[i].color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(data, stp, y, data->sprite[i].color);
		y++;
	}
}

void	set_sprite_limits(t_data *data, int i)
{
	if (data->sprite[i].drawstart_y < 0)
		data->sprite[i].drawstart_y = 0;
	data->sprite[i].drawend_y = data->sprite[i].sprite_h /
	2 + data->screen_height / 2;
	if (data->sprite[i].drawend_y >= data->screen_height)
		data->sprite[i].drawend_y = data->screen_height - 1;
	data->sprite[i].sprite_w = abs((int)(data->screen_height
	/ (data->sprite[i].trans_y)));
	data->sprite[i].drawstart_x = -data->sprite[i].sprite_w
	/ 2 + data->sprite[i].spritescreen_x;
	if (data->sprite[i].drawstart_x < 0)
		data->sprite[i].drawstart_x = 0;
	data->sprite[i].drawend_x = data->sprite[i].sprite_w
	/ 2 + data->sprite[i].spritescreen_x;
	if (data->sprite[i].drawend_x >= data->screen_width)
		data->sprite[i].drawend_x = data->screen_width - 1;
}

void	transform_sprite(t_data *data, int i)
{
	data->sprite[i].calc_x = data->sprite[i].map_x - data->player.x;
	data->sprite[i].calc_y = data->sprite[i].map_y - data->player.y;
	data->sprite[i].inv_det = 1.0 / (data->player.plane_x * data->player.dir_y
	- data->player.dir_x * data->player.plane_y);
	data->sprite[i].trans_x = data->sprite[i].inv_det * (data->player.dir_y
	* data->sprite[i].calc_x - data->player.dir_x * data->sprite[i].calc_y);
	data->sprite[i].trans_y = data->sprite[i].inv_det * (-data->player.plane_y
	* data->sprite[i].calc_x + data->player.plane_x * data->sprite[i].calc_y);
	data->sprite[i].spritescreen_x = (int)((data->screen_width / 2)
	* (1 + data->sprite[i].trans_x / data->sprite[i].trans_y));
	data->sprite[i].sprite_h = abs((int)(data->screen_height
	/ data->sprite[i].trans_y));
	data->sprite[i].drawstart_y = -data->sprite[i].sprite_h
	/ 2 + data->screen_height / 2;
	set_sprite_limits(data, i);
}

void	draw_sprite(t_data *data)
{
	int i;
	int stp;
	int y;

	i = 0;
	while (i < data->sprite_num)
	{
		transform_sprite(data, i);
		stp = data->sprite[i].drawstart_x;
		while (stp < data->sprite[i].drawend_x)
		{
			data->sprite[i].tex_x = (int)(256 * (stp -
			(-data->sprite[i].sprite_w / 2 + data->sprite[i].spritescreen_x)) *
			data->textures.sprite.width / data->sprite[i].sprite_w) / 256;
			if (data->sprite[i].trans_y > 0 && stp > 0 && stp <
			data->screen_width && data->sprite[i].trans_y < data->zbuffer[stp])
			{
				y = data->sprite[i].drawstart_y;
				print_sprite(data, i, stp, y);
			}
			stp++;
		}
		i++;
	}
}
