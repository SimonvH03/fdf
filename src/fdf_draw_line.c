/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/08 19:18:54 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	fdf_draw_point(
		t_fdf	*fdf,
		t_line	*line)
{
	int	x_pixel;
	int	y_pixel;

	x_pixel = line->p0->x + (line->i * line->s_ctl);
	y_pixel = line->p0->y + (line->j * line->s_pas);
	if (!fdf_check_point(fdf, x_pixel, y_pixel))
		mlx_put_pixel(fdf->image,
			x_pixel + fdf->center.x + fdf->offset.x,
			y_pixel + fdf->center.y + fdf->offset.y,
			fdf_line_colour(fdf, line));
}

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

int
	fdf_check_point(
		t_fdf	*fdf,
		int x_pixel,
		int y_pixel)
{
	x_pixel += fdf->center.x + fdf->offset.x;
	y_pixel += fdf->center.y + fdf->offset.y;
	if (x_pixel < 0 || y_pixel < 0
		|| x_pixel >= (int)fdf->image->width
		|| y_pixel >= (int)fdf->image->height)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
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
