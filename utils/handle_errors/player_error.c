/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:32:26 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/03 10:47:06 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	player_error(int type)
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
