/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cycle_palettes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:05:29 by simon             #+#    #+#             */
/*   Updated: 2024/04/19 17:39:34 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_squish(void *param, const int y, const int x)
{
	t_fdf	*fdf;
	t_point	*point;

	fdf = param;
	point = &fdf->map->original[y][x];
	if (fdf->squished)
		point->z *= fdf->squishfactor;
	else
		point->z /= fdf->squishfactor;
}

// from user_inputs_keyscroll.c / keyhook()
void	map_toggle_squish(t_fdf *fdf)
{
	fdf->squished = !fdf->squished;
	map_iteration(fdf->map, &map_squish, fdf);
	fdf->redraw = true;
	map_iteration(fdf->map, &map_set_original, fdf->map);
	fdf->perspective = (t_perspective)
	{ISO_ALPHA, ISO_BETA, ISO_GAMMA, true};
	fdf->ballin = false;
	fdf_center_offset(fdf);
	fdf->scale.diff = fdf->scale.initial * fdf->scale.total;
	fdf->spinlock = false;
	// instead of this bs, enter current preset
}
