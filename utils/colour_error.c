/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:30:38 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 11:31:09 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
