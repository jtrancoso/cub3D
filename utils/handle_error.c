/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:25:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 11:49:00 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	misc_error(t_data *data, int type)
{
	if (type == 20)
	{
		write(1, "Error\nInvalid element descriptor.\n", 34);
		return (0);
	}
	if (type == 9)
	{
		write(1, "Error\nWrong texture identificator.\n", 35);
		return (0);
	}
	return (0);
}

int	handle_error(t_data *data, int type)
{
	if (type >= 0 && type <= 2)
		return (file_error(data, type));
	if (type == 3 || type == 4)
		return (res_error(data, type));
	if (type >= 5 && type < 9)
		return (tex_error(data, type));
	if (type >= 10 && type <= 13)
		return (colour_error(data, type));
	if (type >= 14 && type <= 17)
		return (map_error(data, type));
	if (type == 18 || type == 19)
		return (player_error(data, type));
	if (type == 20 || type == 9)
		return (misc_error(data, type));
	return (0);
}
