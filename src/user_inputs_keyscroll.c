/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_keyscroll.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/16 01:09:27 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
		fdf->map->palette = cycle_palettes(fdf->map);
		if (fdf->ballin == false && fdf->map->palette.nr == P_EARTH_NR)
			fdf->map->palette = cycle_palettes(fdf->map);
		map_iteration(fdf->map, &map_colour, fdf->map);
	}
}

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
