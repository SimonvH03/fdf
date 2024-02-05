/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/05 19:03:13 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	map_free(t_map *map)
{
	int	i;

	i = 0;
	while (map->content[i])
		free(map->content[i++]);
	free(map->content);
}

void	wireframe_free(t_wireframe *wireframe)
{
	free(wireframe->image);
	free(wireframe->map);
	free(wireframe->mlx);
}

void	point_free(t_point *point)
{
	free(point->vector);
}
