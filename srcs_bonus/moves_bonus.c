/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:00:43 by memotyle          #+#    #+#             */
/*   Updated: 2025/03/14 17:31:38 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_wall_collision(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;
	int	id;

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
	if (game->map[map_y][map_x] == 'D')
	{
		id = wich_door(game, map_x, map_y);
		if (game->door[id].barrier_o_c < 3)
			return (1);
	}
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
	game->pics->left = 1;
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
	game->pics->left = 2;
}
