/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:40:43 by saberton          #+#    #+#             */
/*   Updated: 2025/03/08 19:42:35 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	move_view_west(t_game *game)
{
	game->degree -= 1;
	if (game->degree == -1)
		game->degree = 359;
	else if (game->degree == 360)
		game->degree = 0;
	game->angle = ((float)game->degree * M_PI / 180.0) - (0 - (2 * M_PI));
}

static void	move_view_east(t_game *game)
{
	game->degree += 1;
	if (game->degree == -1)
		game->degree = 359;
	else if (game->degree == 360)
		game->degree = 0;
	game->angle = ((float)game->degree * M_PI / 180.0) - (0 - (2 * M_PI));
}

int	render_game(t_game *game)
{
	if (game->keys.north)
		move_north(game);
	else if (game->keys.south)
		move_south(game);
	else if (game->keys.west)
		move_west(game);
	else if (game->keys.east)
		move_east(game);
	if (game->keys.view_west)
		move_view_west(game);
	else if (game->keys.view_east)
		move_view_east(game);
	put_img(game, (M_PI / 3) / game->win_width, (float)game->angle - (M_PI / 6));
	render_mini_map(game);
	render_handlebars(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
