/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:19:35 by jtrancos          #+#    #+#             */
/*   Updated: 2021/01/28 12:51:40 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_to_hex(int colour[3])
{
	int c;

	c = 0;
	c = c + colour[0];
	c = c << 8;
	c = c + colour[1];
	c = c << 8;
	c = c + colour[2];
	return (c);
}