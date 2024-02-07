/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/07 17:01:56 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// content is malloc'd and should be free'd
void	map_free(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->y_max && map->content[i])
		free(map->content[i++]);
	free(map->content);
}

// turn degree angle into radial for stupid math.h functions
double	rad(double angle_deg)
{
	const double	ratio = 180 / PI;

	return (angle_deg / ratio);
}
