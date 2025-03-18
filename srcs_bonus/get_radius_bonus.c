/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_radius_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:38:44 by bertille          #+#    #+#             */
/*   Updated: 2025/03/11 15:45:55 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	len_raycasting(t_game *game, float angle, t_player *hit)
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	float	step_size;

	dx = cos(angle);
	dy = sin(angle);
	x = game->player.x;
	y = game->player.y;
	step_size = 0.1;
	while (game->map[(int)y][(int)x])
	{
		if (game->map[(int)(y + dy * step_size)][(int)(x + dx
                * step_size)] == '1' || game->map[(int)(y + dy
                * step_size)][(int)(x + dx * step_size)] == 'D'
            	|| game->map[(int)(y + dy * step_size)][(int)(x + dx
                * step_size)] == ' ')
			break ;
		x += dx * step_size;
		y += dy * step_size;
	}
	hit->x = x * PX;
	hit->y = y * PX;
}

void	draw_radius(t_game *game, t_player play)
{
	int			i;
	float		angle_step;
	float		angle_start;
	t_player	hit;

	i = 0;
	angle_step = (M_PI / 3) / 180;
	angle_start = (float)game->degree * M_PI / 180.0;
	angle_start -= (M_PI / 6);
	while (i < 180)
	{
		len_raycasting(game, angle_start + i * angle_step, &hit);
		draw_line(game, play, &hit);
		i++;
	}
}
