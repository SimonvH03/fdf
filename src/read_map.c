/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/05 19:03:45 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	map_fill_row(int *map_content_row, char *buffer)
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
		map_content_row[x] = ft_atoi(str_point);
		x++;
	}
}

void	map_fill_content(t_map *map)
{
	char	*buffer;
	int		y;

	map->content = (int **)malloc((map->y_max + 1) * sizeof(int *));
	map->content[map->y_max] = NULL;
	map->fd = open(map->name, O_RDONLY);
	buffer = get_next_line(map->fd);
	y = 0;
	while (buffer && y < map->y_max)
	{
		map->content[y] = (int *)malloc((map->x_max) * sizeof(int));
		map_fill_row(map->content[y], buffer);
		free(buffer);
		y++;
		buffer = get_next_line(map->fd);
	}
	close(map->fd);
}

int	row_size(char *buffer)
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

void	map_size(t_map *map)
{
	char	*buffer;

	map->fd = open(map->name, O_RDONLY);
	buffer = get_next_line(map->fd);
	while (buffer)
	{
		map->x_max = row_size(buffer);
		free(buffer);
		map->y_max++;
		buffer = get_next_line(map->fd);
	}
	close(map->fd);
}


t_map	*read_map(t_map *map)
{
	map_size(map);
	printf("row_size: %d\nrow count: %d\n", map->x_max, map->y_max);
	map_fill_content(map);
	check_map_result(map);
	return (map);
}
