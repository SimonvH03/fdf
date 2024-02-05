/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/05 01:12:51 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	map_fill_row(int *map_content_row, char *buffer)
{
	int		i;
	int		k;
	int		x;
	char	str_element[sizeof(INT_MAX)];

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
			str_element[k] = buffer[i];
			i++;
			k++;
		}
		str_element[k] = '\0';
		map_content_row[x] = ft_atoi(str_element);
		x++;
	}
}

void	map_fill_content(t_map *map)
{
	int		**map_content;
	char	*buffer;
	int		j;

	map_content = (int **)malloc((map->y) * sizeof(int *));
	map->fd = open(map->name, O_RDONLY);
	buffer = get_next_line(map->fd);
	j = 0;
	while (buffer && j < map->y)
	{
		map_content[j] = (int *)malloc((map->x) * sizeof(int));
		map_fill_row(map_content[j], buffer);
		free(buffer);
		j++;
		buffer = get_next_line(map->fd);
	}
	map->content = map_content;
	close(map->fd);
}

int	element_count(char *buffer)
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
		map->x = element_count(buffer);
		free(buffer);
		map->y++;
		buffer = get_next_line(map->fd);
	}
	close(map->fd);
}

// void	check_map_result(t_map *map)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < map->y)
// 	{
// 		x = 0;
// 		while (x < map->x)
// 			{
// 				printf("%d ", map->content[y][x]);
// 				x++;
// 			}
// 		printf("\n");
// 		y++;
// 	}
// }

t_map	*read_map(t_map *map)
{
	map_size(map);
	printf("element_count: %d\nrow count: %d\n", map->x, map->y);
	map_fill_content(map);
	// check_map_result(map);
	map_free(map);
	return (map);
}
