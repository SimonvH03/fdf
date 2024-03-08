/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_presets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:44 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/08 14:36:49 by simon            ###   ########.fr       */
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
		fdf->scale.diff = fdf->scale.initial;
		fdf->ballin = false;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		map_set_original(fdf->map);
		fdf->perspective = (t_perspective)
		{ISO_ALPHA, ISO_BETA, ISO_GAMMA, true};
		fdf->scale.diff = fdf->scale.initial;
		fdf->ballin = false;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
	{
		map_set_polar(fdf->map);
		fdf->perspective = (t_perspective)
		{deg_to_rad(-90), 0, deg_to_rad(90), true};
		fdf->scale.diff = fdf->image->width / (2.2 * fdf->map->radius);
		fdf->scale.total= 1;
		fdf->ballin = true;
	}
}

void
	input_presets_2(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_M))
	{
		fdf->scale.diff = 1 / fdf->scale.total;
		fdf->scale.total= 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_N))
	{
		fdf_center_offset(fdf);
	}
	fdf->spinlock = false;
}
