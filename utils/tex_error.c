/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:33:33 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 11:48:49 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		write(1, "Error\nThere is something wrong with the texture.\n", 49);
		return (0);
	}
	if (type == 8)
	{
		write(1, "Error\nCould not open texture file.\n", 35);
		return (0);
	}
	return (0);
}
