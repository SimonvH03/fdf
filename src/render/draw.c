/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:05:50 by simon             #+#    #+#             */
/*   Updated: 2024/04/19 17:39:34 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void
	draw_orthogonally_adjacent(
		void *param,
		const int y,
		const int x)
{
	const t_fdf		*fdf = param;
	const t_point	*p0 = &fdf->map->project[y][x];
	const int		p0_check = draw_check_point(fdf, p0->x, p0->y);
	t_point			*p1;

	if ((x + 1) < fdf->map->x_max)
	{
		p1 = &fdf->map->project[y][x + 1];
		if (!p0_check || !draw_check_point(fdf, p1->x, p1->y))
			draw_line(fdf, p0, p1);
	}
	if ((y + 1) < fdf->map->y_max)
	{
		p1 = &fdf->map->project[y + 1][x];
		if (!p0_check || !draw_check_point(fdf, p1->x, p1->y))
			draw_line(fdf, p0, p1);
	}
	if ((x + 1) == fdf->map->x_max && fdf->ballin == true)
	{
		p1 = &fdf->map->project[y][0];
		if (!p0_check || !draw_check_point(fdf, p1->x, p1->y))
			draw_line(fdf, p0, p1);
	}
}

// from loop_hooks
void
	draw(
		void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (fdf->redraw == false)
		return ;
	draw_background(fdf->image, fdf->map->palette.background);
	map_iteration(fdf->map, &draw_orthogonally_adjacent, fdf);
	fdf->redraw = false;
}
