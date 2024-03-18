/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graveyard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:00:58 by simon             #+#    #+#             */
/*   Updated: 2024/03/18 02:00:59 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/fdf.h"

// // victim #1: replaced by map_iteration version
// void
// 	fdf_draw(
// 		void *param)
// {
// 	t_fdf	*fdf;
// 	int		y;
// 	int		x;

// 	fdf = param;
// 	if (fdf->redraw == false)
// 		return ;
// 	draw_background(fdf->image, C_BACKGROUND);
// 	y = 0;
// 	while (y < fdf->map->y_max)
// 	{
// 		x = 0;
// 		while (x < fdf->map->x_max)
// 		{
// 			fdf_draw_down_and_to_the_right(fdf, y, x);
// 			x++;
// 		}
// 		y++;
// 	}
// 	fdf->redraw = false;
// }

// // victim #2: replaced by map_iteration version
// void
// 	fdf_colour(
// 		t_fdf	*fdf)
// {
// 	int		x;
// 	int		y;
// 	t_point	*point;

// 	y = 0;
// 	while (y < fdf->map->y_max)
// 	{
// 		x = 0;
// 		while (x < fdf->map->x_max)
// 		{
// 			point = &fdf->map->original[y][x];
// 			point->colour = map_earth_colour(fdf->map, point);
// 			fdf->map->project[y][x].colour = point->colour;
// 			x++;
// 		}
// 		y++;
// 	}
// }

// // victim #3: replaced by map_iteration version

// // parse map and rotate point[x,y,z] values around [0,0,0] (same as fdf_project)
// // this one is for optimization, given the angle of rotation is constant
// // cosin holds the calculated values for cos(fdf.speed) and sin(fdf.speed)
// void
// 	fdf_project_optimized(
// 		t_fdf	*fdf)
// {
// 	t_point	*point;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	while (y < fdf->map->y_max)
// 	{
// 		x = 0;
// 		while (x < fdf->map->x_max)
// 		{
// 			point = &fdf->map->project[y][x];
// 			if (fdf->precalc.gamma || fdf->precalc.beta || fdf->precalc.alpha)
// 				point_rotate_precalculated(fdf, point);
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (fdf->spinlock == false)
// 		fdf->precalc = (t_precalc){0, 0, 0};
// }

// // victim #4: replaced by map_iteration version

// // parse map and rotate point[x,y,z] values around [0,0,0]
// // this function is only for variable angles
// void
// 	fdf_project(
// 		t_fdf	*fdf)
// {
// 	t_point	*point;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	while (y < fdf->map->y_max)
// 	{
// 		x = 0;
// 		while (x < fdf->map->x_max)
// 		{
// 			point = &fdf->map->project[y][x];
// 			if (fdf->perspective.gamma)
// 				point_rotate_gamma(point, fdf->perspective.gamma);
// 			if (fdf->perspective.beta)
// 				point_rotate_beta(point, fdf->perspective.beta);
// 			if (fdf->perspective.alpha)
// 				point_rotate_alpha(point, fdf->perspective.alpha);
// 			x++;
// 		}
// 		y++;
// 	}
// 	fdf->perspective = (t_perspective){0, 0, 0};
// }

// // victim #5: replaced by map_iteration version
// void
// 	fdf_scale(
// 		t_fdf	*fdf)
// {
// 	t_point	*point;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	fdf->offset.x *= fdf->scale.diff;
// 	fdf->offset.y *= fdf->scale.diff;
// 	while (y < fdf->map->y_max)
// 	{
// 		x = 0;
// 		while (x < fdf->map->x_max)
// 		{
// 			point = &fdf->map->project[y][x];
// 			point->x *= fdf->scale.diff;
// 			point->y *= fdf->scale.diff;
// 			point->z *= fdf->scale.diff;
// 			x++;
// 		}
// 		y++;
// 	}
// 	fdf->scale.diff = 1;
// }

// // victim #6: replaced by map_iteration version
// void
// 	map_set_original(
// 		t_map	*map)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			map->project[y][x] = map->original[y][x];
// 			x++;
// 		}
// 		y++;
// 	}
// }

// // victim #7: replaced by map_iteration version
// void
// 	map_fill_polar(
// 		t_map	*map)
// {
// 	int				y;
// 	int				x;
// 	t_point			*point;
// 	const double	longitude_incr = -2 * PI / (map->x_max);
// 	const double	latitude_in = PI / (map->y_max - 1);

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			point = &map->original[y][x];
// 			map->polar[y][x] = (t_point)
// 			{(longitude_incr * x),
// 				(latitude_in * y),
// 				(map->radius + point->z),
// 				point->colour};
// 			x++;
// 		}
// 		y++;
// 	}
// }

// // victim #8: replaced by map_iteration version

// // convert polar coordinates back to cartesian
// // polar is t_point with {(x) beta angle, (y) gamma angle, (z) length}
// // swap polar->y and polar->x for x= and y= for cool projection
// void
// 	map_set_polar(
// 		t_map	*map)
// {
// 	int			y;
// 	int			x;
// 	t_point		*polar;

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			polar = &map->polar[y][x];
// 			map->project[y][x] = (t_point)
// 			{((polar->z) * cos(polar->x) * sin(polar->y)),
// 				((polar->z) * sin(polar->x) * sin(polar->y)),
// 				((polar->z) * cos(polar->y)),
// 				polar->colour};
// 			x++;
// 		}
// 		y++;
// 	}
// }

// // victim #9: replaced by map_iteration version
// void
// 	map_find_z_min_max(
// 		t_map	*map)
// {
// 	int	x;
// 	int	y;
// 	int	z_val;

// 	y = 0;
// 	map->z_min = 0;
// 	map->z_max = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			z_val = map->original[y][x].z;
// 			if (z_val < map->z_min)
// 				map->z_min = z_val;
// 			if (z_val > map->z_max)
// 				map->z_max = z_val;
// 			x++;
// 		}
// 		y++;
// 	}
// 	map->radius = (map->z_max - map->z_min) * 10;
// }
