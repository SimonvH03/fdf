/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/05 01:07:07 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	map_free(t_map *map)
{
	while (map->y--)
		free(map->content[map->y]);
	free(map->content);
}

void	wireframe_free(t_wireframe *wireframe)
{
	free(wireframe->image);
	free(wireframe->map);
	free(wireframe->mlx);
}
