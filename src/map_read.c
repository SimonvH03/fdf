/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/27 19:01:54 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// count elements with subject given map constraints
static int
	map_row_size(
		char *buffer)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (buffer[i])
	{
		while (buffer[i] == ' ')
			i++;
		while (buffer[i] && buffer[i] != ' ')
			i++;
		count++;
	}
	return (count);
}

// count rows with get_next_line
static void
	map_size(
		t_map *map)
{
	char	*buffer;

	map->fd = open(map->name, O_RDONLY);
	map->y_max = 0;
	buffer = get_next_line(map->fd);
	while (buffer)
	{
		map->x_max = map_row_size(buffer);
		free(buffer);
		map->y_max++;
		buffer = get_next_line(map->fd);
	}
	close(map->fd);
}

// parse buffer, extract values with atoi, place [x,y,z] values in t_points
// make a copy at map->project
static void
	map_fill_row(
		t_map *map,
		int y,
		char *buffer)
{
	int		i;
	int		x;
	int		k;
	char	str_z[1 + 10 + 1];

	i = 0;
	x = 0;
	while (buffer[i])
	{
		k = 0;
		while (buffer[i] == ' ')
			i++;
		while (buffer[i] && buffer[i] != ' ' && k < 11)
		{
			str_z[k] = buffer[i];
			k++;
			i++;
		}
		str_z[k] = '\0';
		map->original[y][x] = (t_point)
		{x - (map->x_max / 2), y - (map->y_max / 2), ft_atoi(str_z), 0};
		map->project[y][x] = map->original[y][x];
		x++;
	}
}

// from map_init.c / map_init()
// size up the map, malloc 2D for t_points, fill rows with each get_next_line
// make a copy at map->project to initialize projection data
int
	map_read(
		t_map *map)
{
	char	*buffer;
	int		y;

	map_size(map);
	map->fd = open(map->name, O_RDONLY);
	if (map->fd == -1 || map_malloc_y(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	buffer = get_next_line(map->fd);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	y = 0;
	while (buffer && y < map->y_max)
	{
		if (map_malloc_x(map, y) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		map_fill_row(map, y, buffer);
		free(buffer);
		y++;
		buffer = get_next_line(map->fd);
	}
	close(map->fd);
	return (EXIT_SUCCESS);
}
