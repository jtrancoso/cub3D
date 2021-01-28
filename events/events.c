/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:03:38 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/27 11:05:59 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int		ft_escape(int keycode, t_data *data)
{
	if (keycode == 53)
		ft_close(data);
	return (0);
}

int		press_key(int keycode, t_data *data)
{
	if (keycode == 13)
		data->player.keys.w = 1;
	else if (keycode == 0)
		data->player.keys.a = 1;
	else if (keycode == 1)
		data->player.keys.s = 1;
	else if (keycode == 2)
		data->player.keys.d = 1;
	else if (keycode == 123)
		data->player.keys.left = 1;
	else if (keycode == 124)
		data->player.keys.right = 1;
	return (1);
}

int		release_key(int keycode, t_data *data)
{
	if (keycode == 53)
		ft_close(data);
	else if (keycode == 13)
		data->player.keys.w = 0;
	else if (keycode == 0)
		data->player.keys.a = 0;
	else if (keycode == 1)
		data->player.keys.s = 0;
	else if (keycode == 2)
		data->player.keys.d = 0;
	else if (keycode == 123)
		data->player.keys.left = 0;
	else if (keycode == 124)
		data->player.keys.right = 0;
	return (1);
}
