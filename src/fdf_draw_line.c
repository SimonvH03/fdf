/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/06 19:54:24 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int
	fdf_straight_line(
		t_fdf	*fdf,
		t_line	*line)
{
	if (line->d_ctl == 0)
	{
		while (line->j <= line->d_pas)
		{
			fdf_draw_point(fdf, line);
			line->j++;
		}
		return (1);
	}
	if (line->d_pas == 0)
	{
		while (line->i <= line->d_ctl)
		{
			fdf_draw_point(fdf, line);
			line->i++;
		}
		return (1);
	}
	return (0);
}

void
	fdf_draw_line(
		t_fdf	*fdf,
		t_point	*p0,
		t_point	*p1)
{
	t_line	line;

	if (over_the_horizon(fdf, p0, p1))
		return ;
	fdf_line_init(&line, fdf->map, p0, p1);
	if (fdf_straight_line(fdf, &line))
		return ;
	while (line.i != line.d_ctl)
	{
		fdf_draw_point(fdf, &line);
		while (line.err >= 0)
		{
			line.j += 1;
			line.err -= line.d_ctl;
			fdf_draw_point(fdf, &line);
		}
		line.i += 1;
		line.err += line.d_pas;
	}
	fdf_draw_point(fdf, &line);
}

void
	fdf_draw_full(
		t_fdf	*fdf,
		int x,
		int y)
{
	t_point	*p0;

	p0 = &fdf->map->project[y][x];
	if (fdf_check_point(fdf, p0->x, p0->y))
		return ;
	if ((x + 1) < fdf->map->x_max)
	{
		if (fdf_check_point(fdf, x + 1, y))
			fdf_draw_line(fdf, p0, &fdf->map->project[y][x + 1]);
	}
	if ((y + 1) < fdf->map->y_max)
	{
		if (fdf_check_point(fdf, x, y + 1))
			fdf_draw_line(fdf, p0, &fdf->map->project[y + 1][x]);
	}
	if (fdf->ballin && x == fdf->map->x_max - 1)
	{
		if (fdf_check_point(fdf, 0, y))
			fdf_draw_line(fdf, p0, &fdf->map->project[y][0]);
	}
}
