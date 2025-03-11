/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:59:04 by saberton          #+#    #+#             */
/*   Updated: 2025/03/11 14:53:11 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_ray(t_game *game)
{
	if (game->ray.ray_dir.x < 0)
	{
		game->ray.step.x = -1;
		game->ray.side_dist.x = (game->player.x - game->ray.map.x)
			* game->ray.delta.x;
	}
	else
	{
		game->ray.step.x = 1;
		game->ray.side_dist.x = ((game->ray.map.x + 1.0) - game->player.x)
			* game->ray.delta.x;
	}
	if (game->ray.ray_dir.y < 0)
	{
		game->ray.step.y = -1;
		game->ray.side_dist.y = (game->player.y - game->ray.map.y)
			* game->ray.delta.y;
	}
	else
	{
		game->ray.step.y = 1;
		game->ray.side_dist.y = ((game->ray.map.y + 1.0) - game->player.y)
			* game->ray.delta.y;
	}
}

// static t_img	*choice_pic(t_game *game, t_player *pic)
// {
// 	if (game->ray.side == 0)
// 	{
// 		game->ray.perpwalldist = (game->ray.map.x - game->player.x + (1
// 					- game->ray.step.x) / 2) / game->ray.ray_dir.x;
// 		pic->x = game->player.y + game->ray.perpwalldist * game->ray.ray_dir.y;
// 		if (game->ray.ray_dir.x > 0)
// 			return (game->pics->wall_w);
// 		else
// 			return (game->pics->wall_e);
// 	}
// 	else
// 	{
// 		game->ray.perpwalldist = (game->ray.map.y - game->player.y + (1
// 					- game->ray.step.y) / 2) / game->ray.ray_dir.y;
// 		pic->x = game->player.x + game->ray.perpwalldist * game->ray.ray_dir.x;
// 		if (game->ray.ray_dir.y > 0)
// 			return (game->pics->wall_n);
// 		else
// 			return (game->pics->wall_s);
// 	}
// }

static t_img	*choice_pic(t_game *game, t_player *pic)
{
	char	c;

	c = game->map[(int)game->ray.map.y][(int)game->ray.map.x];
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
	if (c == 'D')
	{
		// Selon la valeur de barrier_o_c, on choisit la texture
		if (game->barrier_o_c == 0)
			return (game->pics->bar_close);
		else if (game->barrier_o_c == 1)
			return (game->pics->bar_semiopen);
		else if (game->barrier_o_c == 2)
			return (game->pics->bar_opopen);
		else // == 3 par exemple
			return (game->pics->bar_open);
	}
	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir.x > 0)
			return (game->pics->wall_w);
		else
			return (game->pics->wall_e);
	}
	else
	{
		if (game->ray.ray_dir.y > 0)
			return (game->pics->wall_n);
		else
			return (game->pics->wall_s);
	}
}

static void	choice_side_wall(t_game *game, t_player *pic)
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
	game->choice_pic = choice_pic(game, pic);
	game->ray.text_step = (float)game->choice_pic->h / game->ray.lineheight;
}

static void	draw_column(t_game *game, int col, t_player *pic)
{
	int	start;
	int	end;
	int	y;
	int	color;

	start = (game->win_height - game->ray.lineheight) / 2;
	if (start < 0)
		start = 0;
	end = (game->win_height + game->ray.lineheight) / 2;
	if (end >= game->win_height)
		end = game->win_height - 1;
	y = 0;
	while (y < start)
		put_pixel_to_img(game, col, y++, game->param->c_colors.dec);
	game->ray.text_step = (float)game->choice_pic->h / game->ray.lineheight;
	game->ray.text_pos = (start - game->win_height / 2 + game->ray.lineheight
			/ 2) * game->ray.text_step;
	// while (y <= end)
	// {
	// 	pic->y = (int)game->ray.text_pos;
	// 	put_pixel_to_img(game, col, y++,
	// 		get_pixel_color(game->choice_pic, pic->x, pic->y));
	// 	game->ray.text_pos += game->ray.text_step;
	// }
	while (y <= end)
	{
		pic->y = (int)game->ray.text_pos;
		color = get_pixel_color(game->choice_pic, pic->x, pic->y);
		if ((color & 0x00FFFFFF) != 0xFF00FF)
			put_pixel_to_img(game, col, y, color);
		y++;
		game->ray.text_pos += game->ray.text_step;
	}
	while (y < game->win_height - 1)
		put_pixel_to_img(game, col, y++, game->param->f_colors.dec);
}

void	put_img(t_game *game, float angle_step, float angle_start)
{
	int			col;
	t_player	pic;
	t_ray		ray;
	float		ray_angle;

	col = 0;
	while (col < game->win_width)
	{
		ray_angle = angle_start + col * angle_step;
		ft_bzero(&ray, sizeof(t_ray));
		ft_bzero(&pic, sizeof(t_player));
		game->ray.camera = 2 * col / (double)game->win_width - 1;
		game->ray.delta.x = fabs(1 / game->ray.ray_dir.x);
		game->ray.delta.y = fabs(1 / game->ray.ray_dir.y);
		game->ray.ray_dir = (t_player){cos(ray_angle), sin(ray_angle)};
		game->ray.map = (t_player){(int)game->player.x, (int)game->player.y};
		init_ray(game);
		game->ray.lineheight = (int)(game->win_height
				/ (game->ray.perpwalldist));
		choice_side_wall(game, &pic);
		pic.x = (int)((pic.x - floor(pic.x)) * (double)game->choice_pic->w);
		draw_column(game, col, &pic);
		col++;
	}
}
