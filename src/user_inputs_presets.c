/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_presets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:44 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/16 17:25:54 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// P for Parallel
// I for Isometric
void
	input_presets_flat(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
	{
		map_iteration(fdf->map, &map_set_original, fdf->map);
		fdf->ballin = false;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		map_iteration(fdf->map, &map_set_original, fdf->map);
		fdf->perspective = (t_perspective)
		{ISO_ALPHA, ISO_BETA, ISO_GAMMA, true};
		fdf->ballin = false;
	}
	fdf_center_offset(fdf);
	fdf->scale.diff = fdf->scale.initial;
	fdf->scale.total = 1;
}

// O for sphere
// U for half sphere
void
	input_presets_balls(
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
	fdf->radius = fdf->map->radius;
	fdf->darksquare = fdf->radius / sqrt(2);
}
