/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_presets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:44 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/11 19:31:57 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	input_presets_1(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
	{
		map_iteration(fdf->map, &map_set_original, fdf->map);
		fdf_reset_scale_and_offset(fdf);
		fdf->ballin = false;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		map_iteration(fdf->map, &map_set_original, fdf->map);
		fdf_reset_scale_and_offset(fdf);
		fdf->perspective = (t_perspective)
		{ISO_ALPHA, ISO_BETA, ISO_GAMMA, true};
		fdf->ballin = false;
	}
}

void
	input_presets_2(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
	{
		fdf->map->shape = (t_shape){S_FULL_SPHERE,
			(-2 * PI / (fdf->map->x_max)),
			(PI / (fdf->map->y_max - 1))};
		fdf->perspective = (t_perspective)
		{deg_to_rad(-90), 0, deg_to_rad(90), true};
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_U))
	{
		fdf->map->shape = (t_shape){S_HALF_SPHERE,
			(-2 * PI / (fdf->map->x_max)),
			(0.5 * PI / (fdf->map->y_max - 1))};
		fdf->perspective = (t_perspective)
		{0, 0, deg_to_rad(90), true};
	}
	map_iteration(fdf->map, &map_fill_polar, fdf->map);
	map_iteration(fdf->map, &map_set_polar, fdf->map);
	fdf_center_offset(fdf);
	fdf->scale.diff = fdf->scale.sphere;
	fdf->scale.total = 1;
	fdf->ballin = true;
}

void
	input_hotkeys(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_M))
	{
		fdf->scale.diff = 1 / fdf->scale.total;
		fdf->scale.total = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_N))
	{
		fdf_center_offset(fdf);
	}
}
