/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/03/09 23:59:16 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// this function sets redraw for values of which the change cannot be checked
void
	fdf_redraw(
		t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_M)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_N))
		fdf->redraw = true;
}

void
	fdf_scale_and_project(
		void	*param)
{
	t_fdf	*fdf;

	fdf = param;
	if (fdf->perspective.reproject
		|| fdf->precalc.reproject
		|| fdf->scale.diff != 1)
		fdf->redraw = true;
	if (fdf->perspective.reproject == true)
	{
		map_iteration(fdf->map, &fdf_project, fdf);
		fdf->perspective = (t_perspective){0, 0, 0, false};
	}
	if (fdf->precalc.reproject == true)
	{
		map_iteration(fdf->map, &fdf_project_optimized, fdf);
		if (fdf->spinlock == false)
			fdf->precalc = (t_precalc){0, 0, 0, false};
	}
	if (fdf->scale.diff != 1)
	{
		fdf->offset.x *= fdf->scale.diff;
		fdf->offset.y *= fdf->scale.diff;
		map_iteration(fdf->map, &fdf_scale, fdf);
		fdf->scale.diff = 1;
	}
}

// victim #5: replaced by map_iteration version

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

void
	fdf_scale(
		const void	*param,
		int y,
		int x)
{
	const t_fdf	*fdf = param;
	t_point	*point;

	point = &fdf->map->project[y][x];
	point->x *= fdf->scale.diff;
	point->y *= fdf->scale.diff;
	point->z *= fdf->scale.diff;
}

void
	fdf_center_offset(
		t_fdf	*fdf)
{
	fdf->center.x = fdf->image->width / 2;
	fdf->center.y = fdf->image->height / 2;
	fdf->offset.x = 0;
	fdf->offset.y = 0;
}	
	
void
	fdf_reset_scale_and_offset(
		t_fdf	*fdf)
{
	fdf_center_offset(fdf);
	fdf->scale.diff = fdf->scale.initial;
	fdf->scale.total = 1;
}
