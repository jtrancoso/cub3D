/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:31:46 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 11:31:57 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
