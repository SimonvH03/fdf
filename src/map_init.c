/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/16 01:24:11 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int
	map_is_globe(
		const char *map_name)
{
	int		name_length;
	char	*search_name;

	if (map_name == NULL)
		return (EXIT_FAILURE);
	name_length = ft_strlen(map_name);
	search_name = ft_strdup(map_name);
	if (search_name == NULL)
		return (EXIT_FAILURE);
	name_length = ft_str_toupper(search_name);
	if (ft_strnstr(search_name, "WORLD", name_length)
		|| ft_strnstr(search_name, "GLOBE", name_length)
		|| ft_strnstr(search_name, "EARTH", name_length)
		|| ft_strnstr(search_name, "WERELD", name_length))
	{
		free(search_name);
		return (EXIT_SUCCESS);
	}
	free(search_name);
	return (EXIT_FAILURE);
}

// from file main.c
int
	map_init(
		t_map *map,
		char *map_name)
{
	map->original = NULL;
	map->project = NULL;
	map->polar = NULL;
	map->palette = (t_palette)
			{P_RGB_NR, C_RGB_BACK,
			C_RGB_LOW, C_RGB_MID, C_RGB_HIGH};
	if (map_is_globe(map_name) == EXIT_SUCCESS)
		map->palette = (t_palette){P_EARTH_NR, C_EARTH_BACK, 0, 0, 0};
	map->name = map_name;
	map->fd = 0;
	if (map_read(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map->z_min = 0;
	map->z_max = 0;
	map_iteration(map, &map_find_z_min_max, map);
	map->total_height = map->z_max - map->z_min;
	map->radius = (map->total_height) * 10;
	map->shape = (t_shape)
			{S_FULL_SPHERE, -2 * PI / (map->x_max), PI / (map->y_max - 1)};
	map_iteration(map , &map_colour, map);
	map_iteration(map, &map_fill_polar, map);
	return (EXIT_SUCCESS);
}
