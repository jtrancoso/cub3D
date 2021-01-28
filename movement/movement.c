/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:09:17 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/27 10:34:43 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_front_back(t_data *data)
{
	if (data->player.keys.w == 1)
	{
		if (data->map.map[(int)(data->player.x + data->player.dir_x *
			data->player.rotation)][(int)(data->player.y)] == '0')
			data->player.x += data->player.dir_x * data->player.rotation;
		if (data->map.map[(int)(data->player.x)][(int)(data->player.y +
			data->player.dir_y * data->player.rotation)] == '0')
			data->player.y += data->player.dir_y * data->player.rotation;
	}
	if (data->player.keys.s == 1)
	{
		if (data->map.map[(int)(data->player.x - data->player.dir_x *
			data->player.rotation)][(int)(data->player.y)] == '0')
			data->player.x -= data->player.dir_x * data->player.rotation;
		if (data->map.map[(int)(data->player.x)][(int)(data->player.y -
			data->player.dir_y * data->player.rotation)] == '0')
			data->player.y -= data->player.dir_y * data->player.rotation;
	}
}

void	move_strafe(t_data *data)
{
	if (data->player.keys.d == 1)
	{
		if (data->map.map[(int)(data->player.x + data->player.dir_y *
			data->player.rotation)][(int)(data->player.y)] == '0')
			data->player.x += data->player.dir_y * data->player.rotation;
		if (data->map.map[(int)(data->player.x)][(int)(data->player.y -
			data->player.dir_x * data->player.rotation)] == '0')
			data->player.y -= data->player.dir_x * data->player.rotation;
	}
	if (data->player.keys.a == 1)
	{
		if (data->map.map[(int)(data->player.x - data->player.dir_y *
			data->player.rotation)][(int)(data->player.y)] == '0')
			data->player.x -= data->player.dir_y * data->player.rotation;
		if (data->map.map[(int)(data->player.x)][(int)(data->player.y +
			data->player.dir_x * data->player.rotation)] == '0')
			data->player.y += data->player.dir_x * data->player.rotation;
	}
}

void	move_player(t_data *data)
{
	data->player.speed = 0.2;
	data->player.rotation = 0.03;
	move_strafe(data);
	move_front_back(data);
	if (data->player.keys.right == 1)
		rotation_right(data);
	if (data->player.keys.left == 1)
		rotation_left(data);
}
