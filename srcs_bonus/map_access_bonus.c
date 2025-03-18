/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_access_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:27:44 by saberton          #+#    #+#             */
/*   Updated: 2025/03/14 18:11:05 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	flood_fill(char **map, t_player cur, t_game *game)
{
	if (cur.y > game->height_map || cur.y < 0
		|| cur.x > (int)ft_strlen(map[(int)cur.y]) || cur.x < 0)
		return ;
	if (map[(int)cur.y][(int)cur.x] == '1' || map[(int)cur.y][(int)cur.x] == 'S'
		|| !map[(int)cur.y][(int)cur.x] || map[(int)cur.y][(int)cur.x] == ' ')
		return ;
	map[(int)cur.y][(int)cur.x] = 'S';
	flood_fill(map, (t_player){cur.x - 1, cur.y}, game);
	flood_fill(map, (t_player){cur.x + 1, cur.y}, game);
	flood_fill(map, (t_player){cur.x, cur.y - 1}, game);
	flood_fill(map, (t_player){cur.x, cur.y + 1}, game);
}

static int	surrounded_by_walls(t_game *game, int y, int x)
{
	if ((y == 0 || y == game->height_map - 1) && (game->check_map[y][x] != '1'
		|| game->check_map[y][x] != ' '))
		return (0);
	if ((x == 0 || x == (int)ft_strlen(game->check_map[y]) - 1)
		&& (game->check_map[y][x] != '1' || game->check_map[y][x] != ' '))
		return (0);
	if (!game->check_map[y - 1][x] || !game->check_map[y + 1][x]
		|| !game->check_map[y][x - 1] || !game->check_map[y][x + 1]
		|| game->check_map[y - 1][x] == ' ' || game->check_map[y + 1][x] == ' '
		|| game->check_map[y][x - 1] == ' ' || game->check_map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	get_height_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	flood_fill_check(t_game *game)
{
	int	i;
	int	j;

	game->height_map = get_height_map(game->check_map);
	flood_fill(game->check_map, game->player, game);
	i = 0;
	while (game->check_map[i])
	{
		j = 0;
		while (game->check_map[i][j])
		{
			if ((game->check_map[i][j] == '0' || game->check_map[i][j] == 'S')
				&& !surrounded_by_walls(game, i, j))
				return (write_err(RED MISS_WALL RESET), 1);
			j++;
		}
		i++;
	}
	return (0);
}
