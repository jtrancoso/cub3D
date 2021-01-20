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
		write(1, "Error\nNot empty line after resolution.\n",39);
		return (0);
	}
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
		write(1, "Error\nThere is something wrong with your texture\n", 49);
		return (0);
	}
	if (type == 8)
	{
		write(1, "Error\nCould not open texture file\n", 34);
		return (0);
	}
}

int	colour_error(t_data *data, int type)
{
	if (type == 9)
	{
		write(1, "Error\nInvalid colour.\n", 22);
		return (0);
	}
	if (type == 10)
	{
		write(1, "Error\nInvalid colour format.\n", 29);
		return (0);
	}
	if (type == 11)
	{
		write(1, "Error\nDuplicated colour.\n", 24);
		return (0);
	}
	if (type == 12)
	{
		write(1, "Error\nNot empty line after colour values.\n", 42);
		return (0);
	}
}
int	handle_error(t_data *data, int type)
{
	if (type >= 0 && type <= 2)
		return (file_error(data, type));
	if (type == 3 || type == 4)
		return (res_error(data, type));
	if (type >= 5 && type <= 8)
		return (tex_error(data, type));
	if (type >= 9 && type <= 12)
		return (colour_error(data, type));
	return (0);
}