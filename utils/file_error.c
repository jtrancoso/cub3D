/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:35:24 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 11:35:32 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
