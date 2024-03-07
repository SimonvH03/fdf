/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/03/07 15:13:48 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
	if (fdf->perspective.reproject)
		fdf_project(fdf);
	if (fdf->precalc.reproject)
		fdf_project_optimized(fdf);
	if (fdf->scale.diff != 1)
		fdf_scale(fdf);
}

void
	fdf_scale(
		t_fdf	*fdf)
{
	t_point	*point;
	int		y;
	int		x;

	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			point = &fdf->map->project[y][x];
			point->x *= fdf->scale.diff;
			point->y *= fdf->scale.diff;
			point->z *= fdf->scale.diff;
			x++;
		}
		y++;
	}
	fdf->scale.diff = 1;
}

void
	fdf_center_offset(
		t_fdf	*fdf)
{
	fdf->offset.x = fdf->image->width / 2;
	fdf->offset.y = fdf->image->height / 2;
}
