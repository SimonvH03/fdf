/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/04 23:26:58 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// int	**fill_content(t_map *map, char *buffer)
// {
// 	int		map_content[map->y][map->x];
// 	char	str_element[sizeof(INT_MAX)];
// 	int		int_element;

	
// 	return (map_content);
// }

int	element_count(char *buffer)
{
	int	count;
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
	if (buffer == NULL)
		return ;
	while (buffer)
	{
		map->x = element_count(buffer);
		free(buffer);
		map->y++;
		buffer = get_next_line(map->fd);
		if (buffer == NULL)
			return ;
	}
	close(map->fd);
}

t_map	*read_map(t_map *map)
{
	map_size(map);
	printf("element_count: %d\nrow count: %d\n", map->x, map->y);

	return (map);
}
