/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:34:35 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/03 10:47:05 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	res_error(int type)
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
	if (type == 25)
	{
		write(1, "Error\nDuplicated resolution line.\n", 34);
		return (0);
	}
	return (0);
}
