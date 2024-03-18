/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_keyscroll.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/18 16:49:10 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from main.c / loop_hooks()
void
	keyhook(
		mlx_key_data_t keydata,
		void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		fdf->spinlock = (!fdf->spinlock);
		fdf->cosin = (t_cosin){cos(fdf->speed), sin(fdf->speed)};
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		fdf->map->palette = map_cycle_palettes(fdf->map);
		if (!fdf->map->isearth && fdf->map->palette.nr == P_EARTH_NR)
			fdf->map->palette = map_cycle_palettes(fdf->map);
		map_iteration(fdf->map, &map_colour, fdf->map);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf_center_offset(fdf);
		fdf->scale.diff = 1 / fdf->scale.total;
		fdf->scale.total = 1;
	}
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		fdf->precalc.sign *= -1;
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
		fdf->horizon = !fdf->horizon;
}

// from main.c / loop_hooks()
void
	scrollhook(
		double xdelta,
		double ydelta,
		void *param)
{
	t_fdf	*fdf;

	fdf = param;
	(void)xdelta;
	if (ydelta)
	{
		fdf->scale.diff *= 1 + (ydelta / 10);
		fdf->scale.total *= 1 + (ydelta / 10);
	}
}
