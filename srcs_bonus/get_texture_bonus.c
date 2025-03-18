/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:23:47 by bertille          #+#    #+#             */
/*   Updated: 2025/03/14 17:34:39 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_text2(int letter, char *str, t_param *param, int i)
{
	if (letter == 3 && !param->we)
	{
		param->we = ft_substr(str, i, ft_strlen(str) - i);
		if (!param->we)
			return (write_err(RED MALLOC RESET), 0);
	}
	if (letter == 4 && !param->ea)
	{
		param->ea = ft_substr(str, i, ft_strlen(str) - i);
		if (!param->ea)
			return (write_err(RED MALLOC RESET), 0);
	}
	return (1);
}

static int	get_text(int letter, char *str, t_param *param, int i)
{
	while (str[i] == ' ')
		i++;
	if (letter == 1 && !param->no)
	{
		param->no = ft_substr(str, i, ft_strlen(str) - i);
		if (!param->no)
			return (write_err(RED MALLOC RESET), 0);
	}
	if (letter == 2 && !param->so)
	{
		param->so = ft_substr(str, i, ft_strlen(str) - i);
		if (!param->so)
			return (write_err(RED MALLOC RESET), 0);
	}
	get_text2(letter, str, param, i);
	return (1);
}

int	map_texture2(t_game *game, t_param *param)
{
	int	we;
	int	ea;
	int	i;

	i = 0;
	we = 0;
	ea = 0;
	while (game->map_file[i])
	{
		if (!ft_strncmp(game->map_file[i], "WE ", 3))
			we += get_text(3, game->map_file[i], param, 3);
		else if (!ft_strncmp(game->map_file[i], "EA ", 3))
			ea += get_text(4, game->map_file[i], param, 3);
		i++;
	}
	if (!param->we || !param->ea)
		return (write_err(RED "Error\nNeeded four param\n" RESET), 1);
	if (!we || we > 1)
		return (write_err(RED "Error\nChoose juste one WE param\n" RESET), 1);
	if (!ea || ea > 1)
		return (write_err(RED "Error\nChoose juste one EA param\n" RESET), 1);
	return (0);
}

int	map_texture(t_game *game, t_param *param)
{
	int	no;
	int	so;
	int	i;

	i = 0;
	no = 0;
	so = 0;
	while (game->map_file[i])
	{
		if (!ft_strncmp(game->map_file[i], "NO ", 3))
			no += get_text(1, game->map_file[i], param, 3);
		else if (!ft_strncmp(game->map_file[i], "SO ", 3))
			so += get_text(2, game->map_file[i], param, 3);
		i++;
	}
	if (!param->no || !param->so)
		return (write_err(RED "Error\nNeeded four param\n" RESET), 1);
	if (!no || no > 1)
		return (write_err(RED "Error\nChoose juste one NO param\n" RESET), 1);
	if (!so || so > 1)
		return (write_err(RED "Error\nChoose juste one SO param\n" RESET), 1);
	return (0);
}

int	path_texture(t_param *param)
{
	int	fd;

	fd = open(param->no, F_OK);
	if (fd == -1)
		return (write_err(RED NO_PATH_NO RESET), 1);
	close(fd);
	fd = open(param->so, F_OK);
	if (fd == -1)
		return (write_err(RED NO_PATH_SO RESET), 1);
	close(fd);
	fd = open(param->we, F_OK);
	if (fd == -1)
		return (write_err(RED NO_PATH_WE RESET), 1);
	close(fd);
	fd = open(param->ea, F_OK);
	if (fd == -1)
		return (write_err(RED NO_PATH_EA RESET), 1);
	return (close(fd), 0);
}
