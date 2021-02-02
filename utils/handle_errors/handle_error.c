/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:25:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/02 11:53:27 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	if (type == 21)
	{
		write(1, "Error\nCould not create screenshot.\n", 35);
		return (0);
	}
	if (type == 22)
	{
		write(1, "Error\nCould not close screenshot file.\n", 39);
		return (0);
	}
	return (0);
}

int	args_error(t_data *data, int type)
{
	if (type == 23)
	{
		write(1, "Error\nIncorrect number of arguments.\n", 37);
		return (0);
	}
	if (type == 24)
	{
		write(1, "Error\nSecond argument must only be '--save'.\n", 45);
		return (0);
	}
	return (0);
}

int	handle_error(t_data *data, int type)
{
	if (type >= 0 && type <= 2)
		return (file_error(data, type));
	if (type == 3 || type == 4 || type == 25)
		return (res_error(data, type));
	if (type >= 5 && type < 9)
		return (tex_error(data, type));
	if (type >= 10 && type <= 13)
		return (colour_error(data, type));
	if (type >= 14 && type <= 17)
		return (map_error(data, type));
	if (type == 18 || type == 19)
		return (player_error(data, type));
	if (type == 20 || type == 9 || type == 21 || type == 22)
		return (misc_error(data, type));
	if (type == 23 || type == 24)
		return (args_error(data, type));
	return (0);
}
