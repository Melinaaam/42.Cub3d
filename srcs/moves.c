/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:43:48 by bertille          #+#    #+#             */
/*   Updated: 2025/03/14 17:31:44 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall_collision(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (game->map[map_y][map_x] == '1')
		return (1);
	if (x - map_x > 1 && game->map[map_y][map_x + 1] == '1')
		return (1);
	if (x - map_x < -0.5 && game->map[map_y][map_x - 1] == '1')
		return (1);
	if (y - map_y > 1 && game->map[map_y + 1][map_x] == '1')
		return (1);
	if (y - map_y < -0.5 && game->map[map_y - 1][map_x] == '1')
		return (1);
	return (0);
}

void	move_north(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + game->dir.x * 0.04;
	new_y = game->player.y + game->dir.y * 0.04;
	if (!is_wall_collision(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall_collision(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_south(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x - game->dir.x * 0.04;
	new_y = game->player.y - game->dir.y * 0.04;
	if (!is_wall_collision(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall_collision(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_west(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x - game->plane.x * 0.04;
	new_y = game->player.y - game->plane.y * 0.04;
	if (!is_wall_collision(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall_collision(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_east(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + game->plane.x * 0.04;
	new_y = game->player.y + game->plane.y * 0.04;
	if (!is_wall_collision(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall_collision(game, game->player.x, new_y))
		game->player.y = new_y;
}
