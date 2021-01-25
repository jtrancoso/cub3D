/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:25:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/25 12:59:46 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_error(t_data *data, int type)
{
	if (type == 0)
	{
		write(1, "Error\nCould not open file.\n", 27);
		return (0);
	}
	else if (type == 1)
	{
		write(1, "Error\nInvalid file extension.\n", 30);
		return (0);
	}
	else if (type == 2)
	{
		write(1, "Error\nCould not close file.\n", 28);
		return (0);
	}
	return (0);
}

int	res_error(t_data *data, int type)
{
	if (type == 3)
	{
		write(1, "Error\nInvalid resolution.\n", 26);
		return (0);
	}
	if (type == 4)
	{
		write(1, "Error\nNot empty line after resolution.\n", 39);
		return (0);
	}
	return (0);
}

int	tex_error(t_data *data, int type)
{
	if (type == 5)
	{
		write(1, "Error\nInvalid texture path.\n", 28);
		return (0);
	}
	if (type == 6)
	{
		write(1, "Error\nDuplicated texture.\n", 26);
		return (0);
	}
	if (type == 7)
	{
		write(1, "Error\nThere is something wrong with your texture.\n", 50);
		return (0);
	}
	if (type == 8)
	{
		write(1, "Error\nCould not open texture file.\n", 35);
		return (0);
	}
	if (type == 9)
	{
		write(1, "Error\nWrong texture identificator.\n", 35);
		return (0);
	}
	return (0);
}

int	colour_error(t_data *data, int type)
{
	if (type == 10)
	{
		write(1, "Error\nInvalid colour.\n", 22);
		return (0);
	}
	if (type == 11)
	{
		write(1, "Error\nInvalid colour format.\n", 29);
		return (0);
	}
	if (type == 12)
	{
		write(1, "Error\nDuplicated colour.\n", 25);
		return (0);
	}
	if (type == 13)
	{
		write(1, "Error\nNot empty line after colour values.\n", 42);
		return (0);
	}
	return (0);
}

int	map_error(t_data *data, int type)
{
	if (type == 14)
	{
		write(1, "Error\nInvalid character in map.\n", 32);
		return (0);
	}
	if (type == 15)
	{
		write(1, "Error\nMap not surrounded by walls at North/South.\n", 50);
		return (0);
	}
	if (type == 16)
	{
		write(1, "Error\nMap not surrounded by walls at West/East.\n", 50);
		return (0);
	}
	if (type == 17)
	{
		write(1, "Error\nMap is not the last element of the file.\n", 47);
		return (0);
	}
	return (0);
}

int	player_error(t_data *data, int type)
{
	if (type == 18)
	{
		write(1, "Error\nCould not find a player.\n", 31);
		return (0);	
	}
	if (type == 19)
	{
		write(1, "Error\nDuplicated player.\n", 25);
		return (0);
	}
	return (0);
}

int	misc_error(t_data * data, int type)
{
	if (type == 20)
	{
		write(1, "Error\nInvalid element descriptor.\n", 34);
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
	if (type >= 5 && type <= 9)
		return (tex_error(data, type));
	if (type >= 10 && type <= 13)
		return (colour_error(data, type));
	if (type >= 14 && type <= 17)
		return (map_error(data, type));
	if (type == 18 || type == 19)
		return (player_error(data, type));
	if (type == 20)
		return (misc_error(data, type));
	return (0);
}
