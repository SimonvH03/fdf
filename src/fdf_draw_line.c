/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/15 19:53:15 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	fdf_draw_point(
		const t_fdf	*fdf,
		const t_line	*line)
{
	int	x_pixel;
	int	y_pixel;

	if (line->swapped == false)
	{
		x_pixel = line->p0->x + (line->i * line->s_ctl);
		y_pixel = line->p0->y + (line->j * line->s_pas);
	}
	else
	{
		x_pixel = line->p0->x + (line->j * line->s_pas);
		y_pixel = line->p0->y + (line->i * line->s_ctl);
	}
	if (!fdf_check_point(fdf, x_pixel, y_pixel))
		mlx_put_pixel(fdf->image,
			x_pixel + fdf->center.x + fdf->offset.x,
			y_pixel + fdf->center.y + fdf->offset.y,
			line_colour(line));
}

static int
	fdf_straight_line(
		const t_fdf	*fdf,
		t_line	*line)
{
	if (line->d_pas == 0)
	{
		while (line->i <= line->d_ctl)
		{
			fdf_draw_point(fdf, line);
			line->i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void
	fdf_draw_line(
		const t_fdf		*fdf,
		const t_point	*p0,
		const t_point	*p1)
{
	t_line	line;

	fdf_line_init(&line, p0, p1);
	if (over_the_horizon(fdf, &line) == EXIT_FAILURE)
		return ;
	if (fdf_straight_line(fdf, &line) == EXIT_SUCCESS)
		return ;
	while (line.i != line.d_ctl)
	{
		fdf_draw_point(fdf, &line);
		if (line.err >= 0)
		{
			fdf_draw_point(fdf, &line);
			line.j += 1;
			line.err -= line.d_ctl;
		}
		line.i += 1;
		line.err += line.d_pas;
	}
	fdf_draw_point(fdf, &line);
}

int
	fdf_check_point(
		const t_fdf	*fdf,
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
		void	*param,
		const int y,
		const int x)
{
	const t_fdf		*fdf = param;
	const t_point	*p0 = &fdf->map->project[y][x];
	const int		p0_check = fdf_check_point(fdf, p0->x, p0->y);
	t_point			*p1;

	if ((x + 1) < fdf->map->x_max)
	{
		p1 = &fdf->map->project[y][x + 1];
		if (!p0_check || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
	if ((y + 1) < fdf->map->y_max)
	{
		p1 = &fdf->map->project[y + 1][x];
		if (!p0_check || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
	if ((x + 1) == fdf->map->x_max && fdf->ballin == true)
	{
		p1 = &fdf->map->project[y][0];
		if (!p0_check || !fdf_check_point(fdf, p1->x, p1->y))
			fdf_draw_line(fdf, p0, p1);
	}
}
