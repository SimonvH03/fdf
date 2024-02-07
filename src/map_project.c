/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:44:02 by simon             #+#    #+#             */
/*   Updated: 2024/02/07 00:53:15 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	point_rotate_alpha(t_point *point, double alpha)
{
	double	prev_y;

	prev_y = point->y;
	point->y = point->y * cos(alpha) + point->z * sin(alpha);
	point->z = prev_y * -sin(alpha) + point->z * cos(alpha);
}

void	point_rotate_beta(t_point *point, double beta)
{
	double	prev_z;

	prev_z = point->z;
	point->z = point->z * cos(beta) + point->x * -sin(beta);
	point->x = prev_z * sin(beta) + point->x * cos(beta);
}

void	point_rotate_gamma(t_point *point, double gamma)
{
	double	prev_x;

	prev_x = point->x;
	point->x = point->x * cos(gamma) + point->y * -sin(gamma);
	point->y = prev_x * sin(gamma) + point->y * cos(gamma);
}

void	point_project(t_point *point, t_perspective *perspective)
{
	point_rotate_alpha(point, perspective->alpha);
	point_rotate_beta(point, perspective->beta);
	point_rotate_gamma(point, perspective->gamma);
}

void	map_project(t_map *map, t_perspective *perspective)
{
	int		y;
	int		x;

	//parse map
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			//put point and matrix into project_point function
			point_project(&map->content[y][x], perspective);
			x++;
		}
		y++;
	}
}
