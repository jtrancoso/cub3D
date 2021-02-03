/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:43:22 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/03 10:51:19 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include "./utils/GNL/get_next_line.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define MAX_SCREENWIDTH 2560
# define MAX_SCREENHEIGHT 1440

typedef struct		s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
	int				esc;
}					t_keys;

typedef struct		s_player
{
	float			x;
	float			y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			rotation;
	float			speed;
	t_keys			keys;

}					t_player;

typedef struct		s_map
{
	char			**map;
	int				height;
	int				width;
	int				inmap;
	int				barra_n;
}					t_map;

typedef struct		s_colour
{
	int				floor[3];
	int				sky[3];
	int				b;
}					t_colour;

typedef struct		s_ray
{
	float			camera_x;
	float			dir_x;
	float			dir_y;
	int				map_x;
	int				map_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			perpwalldist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
}					t_ray;

typedef struct		s_img
{
	void			*img;
	int				*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct		s_texture
{
	int				width;
	int				height;
	char			*path;
	t_img			img;
}					t_texture;

typedef struct		s_textures
{
	t_texture		sprite;
	t_texture		north;
	t_texture		east;
	t_texture		south;
	t_texture		west;
}					t_textures;

typedef struct		s_wall
{
	t_texture		texture;
	int				texture_x;
	int				x;
	float			draw_start;
	float			draw_end;
}					t_wall;

typedef struct		s_sprite
{
	float			map_x;
	float			map_y;
	unsigned int	color;
	float			dist;
	float			calc_x;
	float			calc_y;
	float			inv_det;
	float			trans_x;
	float			trans_y;
	int				spritescreen_x;
	int				sprite_h;
	int				sprite_w;
	int				drawstart_x;
	int				drawstart_y;
	int				drawend_x;
	int				drawend_y;
	int				tex_x;
	int				tex_y;
	int				d;
}					t_sprite;

typedef struct		s_bmp
{
	char			bmpheader[14];
	char			bmpinfo[40];
	int				screenshot;
}					t_bmp;

typedef struct		s_data
{
	void			*mlx;
	void			*win;
	unsigned int	rgb;
	int				blockx;
	int				blocky;
	int				blocklen;
	int				screen_width;
	int				screen_height;
	int				map_height;
	int				map_width;
	int				sprite_num;
	float			*zbuffer;
	t_player		player;
	t_ray			ray;
	t_img			img;
	t_wall			wall;
	t_textures		textures;
	t_sprite		*sprite;
	t_map			map;
	t_colour		colour;
	t_bmp			bmp;
}					t_data;

int					ft_isspace(int c);
void				init_data(t_data *data);
int					empty_line_end(char *line);
int					read_file(t_data *data, const char *file);
int					parse_resolution(t_data *data, char *line);
int					parse_texture(t_data *data, int type, char *line);
int					parse_colour(t_data *data, int type, char *line, int i);
int					check_data(t_data *data);
int					map_count(t_data *data, char *line);
int					parse_map(t_data *data, int fd);
void				flood_fill(t_data *data, int x, int y, int prev_number);
int					check_player(t_data *data, char *line, int y);
void				convert_map(t_data *data);
int					handle_error(int type);
int					colour_error(int type);
int					map_error(int type);
int					player_error(int type);
int					tex_error(int type);
int					res_error(int type);
int					file_error(int type);
int					check_extension(const char *file, char *ext);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				assign_sprite(t_data *data);
void				sort_sprites(t_data *data);
void				draw_texture(t_data *data, t_wall wall, t_ray ray, int x);
void				move_player(t_data *data);
void				rotation_right(t_data *data);
void				rotation_left(t_data *data);
int					ft_close(t_data *data);
int					ft_escape(int keycode, t_data *data);
int					press_key(int keycode, t_data *data);
int					release_key(int keycode, t_data *data);
void				draw_sprite(t_data *data);
int					raycasting(t_data *data);
void				print_sky_wall_floor(t_data *data, int x);
int					rgb_to_hex(int colour[3]);
int					create_bmp(t_data *data);
int					check_args(t_data *data, int argc, char **argv);

#endif
