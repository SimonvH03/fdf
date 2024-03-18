/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/03/18 02:08:29 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from main.c / loop_hooks()
// if the user inputs changed stuff, we recalculate the position of our points
void
	project(
		void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (fdf->perspective.reproject == true)
	{
		map_iteration(fdf->map, &fdf_rotate, fdf);
		fdf->perspective = (t_perspective){0, 0, 0, false};
	}
	if (fdf->precalc.reproject == true)
	{
		map_iteration(fdf->map, &fdf_rotate_optimized, fdf);
		if (fdf->spinlock == false)
			fdf->precalc = (t_precalc){0, 0, 0, 1, false};
	}
	if (fdf->scale.diff != 1)
	{
		fdf->offset.x *= fdf->scale.diff;
		fdf->offset.y *= fdf->scale.diff;
		fdf->radius *= fdf->scale.diff;
		fdf->darksquare *= fdf->scale.diff;
		map_iteration(fdf->map, &fdf_scale, fdf);
		fdf->scale.diff = 1;
	}
}
