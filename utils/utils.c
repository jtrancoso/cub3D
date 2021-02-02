/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:19:35 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/02 12:57:49 by jtrancos         ###   ########.fr       */
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

int	check_args(t_data *data, int argc, char **argv)
{
	if (argc > 3)
		return (handle_error(data, 23));
	if ((argc == 3 && ft_strlen(argv[2]) > 6) ||
		(argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0))
		return (handle_error(data, 24));
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		data->bmp.screenshot = 1;
	return (1);
}
