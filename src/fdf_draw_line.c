/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/07 16:51:56 by svan-hoo         ###   ########.fr       */
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

	fdf_line_init(&line, fdf->map, p0, p1);
	if (over_the_horizon(fdf, &line))
		return ;
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
	fdf_draw_down_and_to_the_right(
		t_fdf	*fdf,
		int x,
		int y)
{
	t_point	*p0;
	t_point	*p1;
	int		check0;

	p0 = &fdf->map->project[y][x];
	check0 = fdf_check_point(fdf, p0->x, p0->y);
	if ((x + 1) < fdf->map->x_max)
	{
		p1 = &fdf->map->project[y][x + 1];
		if (!check0 || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
	if ((y + 1) < fdf->map->y_max)
	{
		p1 = &fdf->map->project[y + 1][x];
		if (!check0 || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
	if (fdf->ballin == true && x == fdf->map->x_max - 1)
	{
		p1 = &fdf->map->project[y][0];
		if (!check0 || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
}
