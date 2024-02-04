/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/04 22:36:35 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	map_init(t_map *map)
{
	map->content = NULL;
	map->fd = 0;
	map->name = NULL;
	map->x = 0;
	map->y = 0;
}

void	wireframe_init(t_wireframe *wireframe)
{
	wireframe->image = NULL;
	wireframe->map = NULL;
	wireframe->mlx = NULL;
}
