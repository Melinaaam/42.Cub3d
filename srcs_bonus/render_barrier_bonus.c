/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_barrier_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:35:19 by memotyle          #+#    #+#             */
/*   Updated: 2025/03/17 10:43:08 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_img	*choice_pic(t_game *game, t_player *pic)
{
	int	id;

	if (game->ray.side == 0)
	{
		game->ray.perpwalldist = (game->ray.map.x - game->player.x + (1
					- game->ray.step.x) / 2) / game->ray.ray_dir.x;
		pic->x = game->player.y + game->ray.perpwalldist * game->ray.ray_dir.y;
	}
	else
	{
		game->ray.perpwalldist = (game->ray.map.y - game->player.y + (1
					- game->ray.step.y) / 2) / game->ray.ray_dir.y;
		pic->x = game->player.x + game->ray.perpwalldist * game->ray.ray_dir.x;
	}
	id = wich_door(game, (int)game->ray.map.x, (int)game->ray.map.y);
	if (game->door[id].barrier_o_c == 0 && id != -1)
		return (game->pics->bar_close);
	else if (game->door[id].barrier_o_c == 1 && id != -1)
		return (game->pics->bar_semiopen);
	else if (game->door[id].barrier_o_c == 2 && id != -1)
		return (game->pics->bar_opopen);
	else if (game->door[id].barrier_o_c == 3 && id != -1)
		return (game->pics->bar_open);
	return (NULL);
}

static char	wall_or_door(t_game *game)
{
	char	c;
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (game->ray.side_dist.x < game->ray.side_dist.y)
		{
			game->ray.side_dist.x += game->ray.delta.x;
			game->ray.map.x += game->ray.step.x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist.y += game->ray.delta.y;
			game->ray.map.y += game->ray.step.y;
			game->ray.side = 1;
		}
		c = game->map[(int)game->ray.map.y][(int)game->ray.map.x];
		if (c == '1' || c == 'D')
			hit = 1;
	}
	return (c);
}

static int	init_column(t_game *game, t_player *pic)
{
	int	start;

	start = (game->win_height - game->ray.lineheight) / 2 + 1;
	if (start < 0)
		start = 0;
	game->choice_pic = choice_pic(game, pic);
	game->ray.text_step = (float)game->choice_pic->h / game->ray.lineheight;
	pic->x = (int)((pic->x - floor(pic->x)) * (double)game->choice_pic->w);
	game->ray.text_step = (float)game->choice_pic->h / game->ray.lineheight;
	game->ray.text_pos = (start - game->win_height / 2 + game->ray.lineheight
			/ 2) * game->ray.text_step;
	return (start);
}

static void	draw_column(t_game *game, int col, t_player *pic)
{
	int	start;
	int	end;
	int	y;
	int	color;

	start = init_column(game, pic);
	end = (game->win_height + game->ray.lineheight) / 2;
	if (end >= game->win_height)
		end = game->win_height - 1;
	y = 0;
	while (y < start)
		y++;
	while (y <= end)
	{
		pic->y = (int)game->ray.text_pos;
		color = get_pixel_color(game->choice_pic, pic->x, pic->y);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel_to_img(game, col, y, color);
		y++;
		game->ray.text_pos += game->ray.text_step;
	}
	while (y < game->win_height)
		y++;
}

void	put_img_door(t_game *game, float angle_step, float angle_start)
{
	int			col;
	float		ray_angle;
	t_player	pic;
	t_ray		ray;

	toggle_barrier(game, (int)game->ray_door.map.x, (int)game->ray_door.map.y);
	col = 0;
	while (col < game->win_width)
	{
		ray_angle = angle_start + col * angle_step;
		ft_bzero(&ray, sizeof(t_ray));
		ft_bzero(&pic, sizeof(t_player));
		game->ray.camera = 2 * col / (double)game->win_width - 1;
		game->ray.ray_dir.x = game->dir.x + game->plane.x * game->ray.camera;
		game->ray.ray_dir.y = game->dir.y + game->plane.y * game->ray.camera;
		game->ray.delta.x = fabs(1 / game->ray.ray_dir.x);
		game->ray.delta.y = fabs(1 / game->ray.ray_dir.y);
		game->ray.map = (t_player){(int)game->player.x, (int)game->player.y};
		init_ray(game);
		game->ray.lineheight = (int)(game->win_height
				/ (game->ray.perpwalldist));
		if (wall_or_door(game) == 'D')
			draw_column(game, col, &pic);
		col++;
	}
}
