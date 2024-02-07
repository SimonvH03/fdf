/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/07 02:35:22 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// count elements with subject given map constraints
static int	map_row_size(char *buffer)
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
static void	map_size(t_map *map)
{
	char	*buffer;

	map->fd = open(map->name, O_RDONLY);
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
static void	map_fill_row(t_point **content, int y, char *buffer)
{
	int		i;
	int		k;
	int		x;
	char	str_point[sizeof(INT_MAX)];

	i = 0;
	k = 0;
	x = 0;
	while (buffer[i])
	{
		k = 0;
		while (buffer[i] == ' ')
			i++;
		while (buffer[i] && buffer[i] != ' ')
		{
			str_point[k] = buffer[i];
			i++;
			k++;
		}
		str_point[k] = '\0';
		content[y][x] = (t_point){x, y, ft_atoi(str_point), C_LINES};
		x++;
	}
}

// size up the map, malloc 2D for t_points, fill rows with each get_next_line
void	map_fill_content(t_map *map)
{
	char	*buffer;
	int		y;

	map_size(map);
	map->content = (t_point **)malloc((map->y_max + 1) * sizeof(t_point *));
	map->fd = open(map->name, O_RDONLY);
	buffer = get_next_line(map->fd);
	y = 0;
	while (buffer && y < map->y_max)
	{
		map->content[y] = (t_point *)malloc((map->x_max + 1) * sizeof(t_point));
		map_fill_row(map->content, y, buffer);
		free(buffer);
		y++;
		buffer = get_next_line(map->fd);
	}
	close(map->fd);
}
