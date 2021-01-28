/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:09:15 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/27 10:34:05 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotation_right(t_data *data)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(-data->player.rotation) -
						data->player.dir_y * sin(-data->player.rotation);
	data->player.dir_y = old_dir_x * sin(-data->player.rotation) +
						data->player.dir_y * cos(-data->player.rotation);
	data->player.plane_x = data->player.plane_x * cos(-data->player.rotation) -
						data->player.plane_y * sin(-data->player.rotation);
	data->player.plane_y = old_plane_x * sin(-data->player.rotation) +
						data->player.plane_y * cos(-data->player.rotation);
}

void	rotation_left(t_data *data)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(data->player.rotation) -
						data->player.dir_y * sin(data->player.rotation);
	data->player.dir_y = old_dir_x * sin(data->player.rotation) +
						data->player.dir_y * cos(data->player.rotation);
	data->player.plane_x = data->player.plane_x * cos(data->player.rotation) -
						data->player.plane_y * sin(data->player.rotation);
	data->player.plane_y = old_plane_x * sin(data->player.rotation) +
						data->player.plane_y * cos(data->player.rotation);
}
