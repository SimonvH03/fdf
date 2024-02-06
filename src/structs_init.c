/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/06 10:59:14 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_map	map_init(char *map_name)
{
	t_map	map;

	map.content = NULL;
	map.fd = 0;
	map.name = map_name;
	map.x_max = 0;
	map.y_max = 0;
	return (map);
}

t_fdf	fdf_init(t_map *map)
{
	t_fdf	fdf;

	fdf.image = NULL;
	fdf.map = map;
	fdf.mlx = NULL;
	return (fdf);
}
