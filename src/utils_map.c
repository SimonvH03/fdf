/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/11 15:49:07 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from map_read.c
int
	map_malloc_y(
		t_map	*map)
{
	map->original = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->original == NULL)
		return (EXIT_FAILURE);
	map->project = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->project == NULL)
		return (EXIT_FAILURE);
	map->polar = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->polar == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int
	map_malloc_x(
		t_map	*map,
		const int y)
{
	map->original[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (map->original[y] == NULL)
		return (EXIT_FAILURE);
	map->project[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (map->project[y] == NULL)
		return (EXIT_FAILURE);
	map->polar[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (map->polar[y] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void
	map_find_z_min_max(
		void	*param,
		const int y,
		const int x)
{			
	t_map	*map;
	int		z_val;

	map = param;
	z_val = map->original[y][x].z;
	if (z_val < map->z_min)
		map->z_min = z_val;
	if (z_val > map->z_max)
		map->z_max = z_val;
}

// from main.c
void
	map_free(
		t_map	*map)
{
	int	i;

	i = 0;
	while (i < map->y_max && map->project[i])
		free(map->project[i++]);
	free(map->project);
	i = 0;
	while (i < map->y_max && map->polar[i])
		free(map->polar[i++]);
	free(map->polar);
	i = 0;
	while (i < map->y_max && map->original[i])
		free(map->original[i++]);
	free(map->original);
}

int
	map_is_globe(
		const char	*map_name)
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
