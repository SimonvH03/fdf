/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/06 18:30:55 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int
	fdf_straight_line(
		t_fdf *fdf,
		t_line *line)
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
		t_fdf *fdf,
		t_point *p0,
		t_point *p1)
{
	t_line	line;

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

static int
	fdf_check_point(
		t_fdf *fdf,
		int x_pixel,
		int y_pixel)
{
	x_pixel += fdf->x_offset;
	y_pixel += fdf->y_offset;
	if (x_pixel < 0)
		return (1);
	if (y_pixel < 0)
		return (2);
	if (x_pixel >= (int)fdf->image->width)
		return (3);
	if (y_pixel >= (int)fdf->image->height)
		return (4);
	return (0);
}

void
	fdf_draw_full(
		t_fdf *fdf,
		int x,
		int y)
{
	t_point	*p0;
	t_point	*p1;
	int		bound0;

	p0 = &fdf->map->project[y][x];
	bound0 = fdf_check_point(fdf, p0->x, p0->y);
	if ((x + 1) < fdf->map->x_max)
	{
		p1 = &fdf->map->project[y][x + 1];
		if (!bound0 || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
	if ((y + 1) < fdf->map->y_max)
	{
		p1 = &fdf->map->project[y + 1][x];
		if (!bound0 || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
	if (fdf->ballin && (x + 1) == fdf->map->x_max)
	{
		p1 = &fdf->map->project[y][0];
		if (!bound0 || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
}
