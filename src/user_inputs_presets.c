/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_presets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:44 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/06 19:56:00 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	input_presets_1(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
	{
		map_set_original(fdf->map);
		fdf_recenter(fdf);
		fdf->scalediff = fdf->init_scale;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		map_set_original(fdf->map);
		*fdf->perspective = (t_perspective){ISO_ALPHA, ISO_BETA, ISO_GAMMA};
		fdf_recenter(fdf);
		fdf->scalediff = fdf->init_scale;
	}
	fdf->ballin = false;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
	{
		map_set_polar(fdf->map);
		*fdf->perspective = (t_perspective){deg_to_rad(270), 0, deg_to_rad(90)};
		fdf->scalediff = fdf->image->width / (2.2 * fdf->map->radius);
		fdf->scale = 1;
		fdf->ballin = true;
	}
	fdf->spinlock = false;
	fdf->redraw = true;
}

void
	input_presets_2(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_M))
	{
		fdf->scalediff = 1 / fdf->scale;
		fdf->scale = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_N))
	{
		fdf_recenter(fdf);
	}
	fdf->spinlock = false;
	fdf->redraw = true;
}
