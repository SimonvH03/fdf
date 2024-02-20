/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/20 23:45:46 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t	fdf_colour(t_line *line)
{
	return (C_LINES);
}

static int	fdf_draw_point(t_fdf *fdf, t_line *line)
{
	int	x_pixel;
	int	y_pixel;

	x_pixel = line->xi + fdf->x_offset;
	y_pixel = line->yi + fdf->y_offset;
	if (x_pixel < fdf->image->width && y_pixel < fdf->image->height
		&& x_pixel > 0 && y_pixel > 0)
	{
		mlx_put_pixel(fdf->image, x_pixel, y_pixel, fdf_colour(line));
		// printf("bounds: %d\ty: %u\nline.a: %f\tline.a2: %f\tline.dy: %f\tline.dx: %f\n", fdf->image->width, y_pixel, line->a, line->a2, line->dy, line->dx);
	}
	else
	{
		// printf("bounds: %d\tx: %d\nline.a: %f\tline.a2: %f\tline.dy: %f\tline.dx: %f\n", fdf->image->width, x_pixel, line->a, line->a2, line->dy, line->dx);
		// printf("bounds: %d\ty: %d\n", fdf->image->height, y_pixel);
		return (-1);
	}
	return (0);
}

static void	fdf_draw_line(t_fdf *fdf, const t_point *p0, const t_point *p1)
{
	t_line	line;

	line.dx = p1->x - p0->x;
	line.dy = p1->y - p0->y;
	if (p0->x >= p1->x || line.dy > line.dx)
		return ;
	line.xi = p0->x;
	line.yi = p0->y;
	line.sy = 1;
	if (p0->y > p1->y)
		line.sy = -1;
	while (line.xi <= p1->x)
	{
		line.err = line.dx - line.dy;
		if (line.err > line.dy)
		{
			line.yi += line.sy;
			line.err += line.dy;
		}
		fdf_draw_point(fdf, &line);
		line.xi += 1;
	}
	
}

void	fdf_draw(void *param)
{
	t_fdf	*fdf;
	int		y;
	int		x;

	fdf = param;
	draw_background(fdf->image, C_BACKGROUND);
	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			if ((x + 1) < fdf->map->x_max)
				fdf_draw_line(fdf, &fdf->map->project[y][x],
					&fdf->map->project[y][x + 1]);
			if ((y + 1) < fdf->map->y_max)
				fdf_draw_line(fdf, &fdf->map->project[y][x],
					&fdf->map->project[y + 1][x]);
			x++;
		}
		y++;
	}
}
