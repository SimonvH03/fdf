/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/05 18:58:42 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_map	*map_init(char *map_name)
{
	t_map	map;

	map.content = NULL;
	map.fd = 0;
	map.name = map_name;
	map.x_max = 0;
	map.y_max = 0;
	return (&map);
}

t_wireframe	*wireframe_init(t_map *map)
{
	t_wireframe	wireframe;

	wireframe.image = NULL;
	wireframe.map = NULL;
	wireframe.mlx = NULL;
	return (&wireframe);
}

t_vector	*vector_init(void)
{
	t_vector	vector;

	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	return (&vector);
}

t_point	*point_init(t_vector *vector)
{
	t_point	point;

	point.vector = vector;
	point.colour = C_LINES;
	return (&point);
}

t_rotation_matrix	*rotation_matrix_init(void)
{
	t_rotation_matrix	rotation_matrix;

	rotation_matrix.alpha = 0;
	rotation_matrix.beta = 0;
	rotation_matrix.gamma = 0;
	return (&rotation_matrix);
}
