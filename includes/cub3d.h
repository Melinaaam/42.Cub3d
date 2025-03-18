/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:55:54 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/14 17:31:42 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "define.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <unistd.h>

typedef struct s_colors
{
	int			r;
	int			g;
	int			b;
	int			dec;
}				t_colors;

typedef struct s_img
{
	void		*img;
	int			bpp;
	int			line_len;
	int			w_height;
	int			w_width;
	int			endian;
	char		*addr;
}				t_img;

typedef struct s_param
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*floor_color;
	char		*ceiling_color;
	t_colors	f_colors;
	t_colors	c_colors;
}				t_param;

typedef struct s_pics
{
	t_img		*wall_n;
	t_img		*wall_s;
	t_img		*wall_w;
	t_img		*wall_e;
}				t_pics;

typedef struct s_player
{
	float		x;
	float		y;
}				t_player;

typedef struct s_keys
{
	int			north;
	int			south;
	int			west;
	int			east;
	int			view_west;
	int			view_east;
}				t_keys;

typedef struct s_ray
{
	int			side;
	int			lineheight;
	double		camera;
	double		perpwalldist;
	float		text_pos;
	float		text_step;
	t_player	map;
	t_player	ray_dir;
	t_player	delta;
	t_player	step;
	t_player	side_dist;
}				t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			map_fd;
	int			height_map;
	float		degree;
	float		angle;
	char		**map_file;
	char		**map;
	char		**check_map;
	t_player	player;
	t_player	dir;
	t_player	plane;
	t_keys		keys;
	t_ray		ray;
	t_param		*param;
	t_pics		*pics;
	t_img		img;
	t_img		*choice_pic;
}				t_game;

// ---------------- check_map_file.c -------------------------
int				check_map_file(char *map_file, t_game *game);

// ---------------- free.c -------------------------
void			free_all(t_game *game);
void			quite_game(t_game *game);

// ---------------- get_texture.c -------------------------
int				map_texture2(t_game *game, t_param *param);
int				map_texture(t_game *game, t_param *param);
int				path_texture(t_param *param);

// ---------------- map_file_parse.c -------------------------
void			map_file_parse(t_game *game);

// ---------------- create_rgb.c -------------------------
int				create_rgb(t_game *game, int r, int g, int b);

// ---------------- recup_color.c -------------------------
int				map_color(t_game *game, t_param *param);

// ---------------- check_color.c -------------------------
int				check_value(t_game *game, t_param *param);

// ---------------- map_parse.c -------------------------
int				recup_map(char **file, t_game *game);
int				check_char(char **map, t_game *game);

// ---------------- map_access.c.c -------------------------
int				flood_fill_check(t_game *game);

// ---------------- utils.c -------------------------
void			write_err(char *str);
void			put_pixel_to_img(t_game *game, int x, int y, int color);
int				get_pixel_color(t_img *texture, int x, int y);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*substring_until_char(const char *str, char delimiter);

// ---------------- moves.c-----------------------
void			move_north(t_game *game);
void			move_south(t_game *game);
void			move_west(t_game *game);
void			move_east(t_game *game);

// ---------------- render_game.c-----------------------
int				render_game(t_game *game);

// ---------------- put_img.c-----------------------
void			put_img(t_game *game, float angle_step, float angle_start);

// ---------------- main.c -------------------------

#endif