/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:20:22 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/17 11:04:05 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_map(int fd)
{
	char	*map_data;
	char	*buff;
	char	*temp;
	int		read_return ;

	buff = ft_calloc((10000 + 1), sizeof(char));
	if (!buff)
		return (NULL);
	read_return = 1;
	map_data = NULL;
	map_data = ft_strdup("");
	while (read_return)
	{
		read_return = (read(fd, buff, 10000));
		if (read_return == -1)
			return (free(map_data), free(buff), NULL);
		buff[read_return] = '\0';
		temp = map_data;
		map_data = ft_strjoin(map_data, buff);
		free(temp);
	}
	if (!map_data || !map_data[0])
		return (free(map_data), free(buff), NULL);
	return (free(buff), map_data);
}

static int	check_extension(char *file_name)
{
	int	i;
	int	_return_;

	i = ft_strlen(file_name);
	if (i < 4)
		return (0);
	_return_ = ft_strncmp(file_name + i - 4, ".cub", 4);
	return (_return_ == 0);
}

int	check_map_file(char *map_file, t_game *game)
{
	char	*file_map_content;

	file_map_content = NULL;
	if (!check_extension(map_file))
		return (write_err(RED "Error\nIncorrect map file\n" RESET), 1);
	game->map_fd = open(map_file, O_RDONLY);
	if (game->map_fd < 0)
		return (write_err(RED "Error\nMap file exist ?!\n" RESET), 1);
	file_map_content = read_map(game->map_fd);
	if (!file_map_content)
		return (close(game->map_fd),
			write_err(RED "Error\nMap empty ?!\n" RESET), 1);
	game->map_file = ft_split(file_map_content, '\n');
	if (!game->map_file)
		return (free(file_map_content), close(game->map_fd), 1);
	free(file_map_content);
	close(game->map_fd);
	return (0);
}
