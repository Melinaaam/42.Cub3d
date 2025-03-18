/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:55:54 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/14 17:31:40 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "define.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

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
	int			h;
	int			w;
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
	int			left;
	int			step;
	long long	start_sprite;
	long long	end_sprite;
	t_img		*wall_n;
	t_img		*wall_s;
	t_img		*wall_w;
	t_img		*wall_e;
	t_img		*straight;
	t_img		*left_0;
	t_img		*left_1;
	t_img		*right_0;
	t_img		*right_1;
	t_img		*bar_open;
	t_img		*bar_close;
	t_img		*bar_semiopen;
	t_img		*bar_opopen;
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
typedef struct s_door
{
	int			id;
	int			step;
	int			barrier_o_c;
	int			barrier_framecount;
	t_player	pos;
}				t_door;
typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			map_fd;
	int			height_map;
	int			barrier_nb;
	int			barrier_open;
	float		degree;
	float		angle;
	char		**map_file;
	char		**map;
	char		**check_map;
	t_player	player;
	t_player	dir;
	t_player	plane;
	t_player	mouse;
	t_keys		keys;
	t_ray		ray;
	t_param		*param;
	t_pics		*pics;
	t_img		img;
	t_img		*choice_pic;
	t_img		*player_sprite;
	t_ray		ray_door;
	t_door		*door;
}				t_game;

// ---------------- check_map_file_bonus.c -------------------------
int				check_map_file(char *map_file, t_game *game);

// ---------------- free_bonus.c -------------------------
void			free_all(t_game *game);

// ---------------- get_texture_bonus.c -------------------------
int				map_texture2(t_game *game, t_param *param);
int				map_texture(t_game *game, t_param *param);
int				path_texture(t_param *param);

// ---------------- map_file_parse_bonus.c -------------------------
void			map_file_parse(t_game *game);

// ---------------- create_rgb_bonus.c -------------------------
int				create_rgb(t_game *game, int r, int g, int b);

// ---------------- recup_color_bonus.c -------------------------
int				map_color(t_game *game, t_param *param);

// ---------------- check_color_bonus.c -------------------------
int				check_value(t_game *game, t_param *param);

// ---------------- map_parse_bonus.c -------------------------
int				recup_map(char **file, t_game *game);
int				check_char(char **map, t_game *game);

// ---------------- map_parse_door_bonus.c -------------------------
int				door_surrounded(t_game *game);
int				check_one_door(t_game *game, int i, int j);
int				map_parse_door(t_game *game, char **map);

// ---------------- map_access_bonus.c.c -------------------------
int				flood_fill_check(t_game *game);

// ---------------- utils_bonus.c -------------------------
void			write_err(char *str);
void			put_pixel_to_img(t_game *game, int x, int y, int color);
int				get_pixel_color(t_img *texture, int x, int y);
long long		timestamp(void);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*substring_until_char(const char *str, char delimiter);

// ---------------- init_game_bonus.c -------------------------
void			mlx_initialize(t_game *game);

// ---------------- moves_bonus.c-----------------------
void			move_north(t_game *game);
void			move_south(t_game *game);
void			move_west(t_game *game);
void			move_east(t_game *game);

// ---------------- get_radius_bonus.c-----------------------
void			len_raycasting(t_game *game, float angle, t_player *hit);
void			draw_radius(t_game *game, t_player play);

// ---------------- render_mini_map_bonus.c-----------------------
void			draw_line(t_game *game, t_player play, t_player *hit);
void			render_mini_map(t_game *game);

// ---------------- update_handlebars_bonus.c-----------------------
void			update_animation(t_game *game);

// ---------------- render_handlebars_bonus.c-----------------------
void			render_handlebars(t_game *game);

// ---------------- mouse_bonus.c-----------------------
int				mouse_move(int x, int y, t_game *game);
int				mouse_press(int button, int x, int y, t_game *game);

// ---------------- ray_to_door_bonus.c-----------------------
char			get_ray_to_door(t_game *game, int x);

// ---------------- barrier_bonus.c-----------------------
void			toggle_barrier(t_game *game, int x, int y);
int				wich_door(t_game *game, int x, int y);

// ---------------- render_handlebars_bonus.c-----------------------
void			put_img_door(t_game *game, float angle_step, float angle_start);

// ---------------- render_game_bonus.c-----------------------
void			move_view_west(t_game *game);
void			move_view_east(t_game *game);
int				render_game(t_game *game);

// ---------------- put_img_bonus.c-----------------------
void			init_ray(t_game *game);
void			put_img(t_game *game, float angle_step, float angle_start);

// ---------------- main_bonus.c -------------------------
void			quite_game(t_game *game);

#endif