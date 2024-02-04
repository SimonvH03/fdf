/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/04 18:19:48 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	**fill_content(t_map *map, char *buffer)
// {
// 	int		**map_content;
// 	int		*content;
// 	char	str_element[sizeof(INT_MAX)];
// 	int		int_element;


// 	return (map_content);
// }

int	map_size(t_map *map)
{
	char	*buffer;
	int		i;
	int		element_count;

	element_count = 1;
	map->y = 1;
	buffer = get_next_line(map->fd);
	while (buffer)
	{
		i = 0;
		element_count = 1;
		while (buffer[i])
		{
			while (ft_isalpha(buffer[i]))
				i++;
			if (buffer[i] == ' ')
				element_count++;
		}
		if (element_count != map->x)
			printf("element_count != map->x");
		map->x = element_count;
		map->y++;
	}
	return (0);
}

t_map	*read_map(t_map *map)
{
	map_size(map);

	return (map);
}
