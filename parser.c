/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:27:38 by jtrancos          #+#    #+#             */
/*   Updated: 2020/12/04 11:43:45 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** 1º Leemos el .cub con read
** 2º limpiamos todos los espacios
** 3º tenemos que ver que tipo de linea tenemos (text, resolucion, color, etc)
** 4º R: guardamos primer numero en anchura y segundo en altura
** 5º NSEW: guardamos la texturas 
** 6º CF: guardamos color de cielo o suelo y lo pasamos a hexa 
** 7º 012: guardamos el mapa y quitamos espacios si los hubiera
**
**
**
**
**
**
*/

int	check_extension(const char *file, char *ext)
{
	size_t	len;
	size_t	ext_len;
	char	*tmp;

	len = ft_strlen(file);
	ext_len = ft_strlen(ext);

	if (len < ext_len)
	{
		write(1, "Error. Invalid file.\n", 21);
		return (0);
	}
	tmp = ft_substr(file, len - ext_len, ext_len);
	if (ft_strncmp(tmp, ext, 4) == 0)
	{
		free(tmp);
		return (1);
	}
	write(1, "Error. Invalid file.\n", 21);
	free (tmp);
	return (0);
}

int	check_file(t_data *data, const char *file, int fd)
{
	int		ret;
	char	*line;
	int		correct_line;

	check_extension(file, ".cub");
	return (0);
}

int read_file(t_data *data, const char *file)
{
	int fd;

	//init_data(data);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(1, "error\n", 6);
		return (0);
	}
	check_file(data, file, fd);
	return (0);
	//check_file;


}

int	main(int argc, char **argv)
{
	check_extension(argv[1], ".cub");
	return (0);
}
