/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/20 21:12:07 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	fdf_line_init(t_line *line, const t_point *p0, const t_point *p1)
{
	line->dx = p1->x - p0->x;
	line->dy = p1->y - p0->y;


	
	line->xi = p0->x;
	line->yi = p0->y;
	line->sx = ft_sign(line->dx);
	line->sy = ft_sign(line->dy);
	line->dx *= line->sx;
	line->dy *= line->sy;
	line->a = line->dx - line->dy;
	line->z0 = p0->z;
	line->z1 = p1->z;
}

int	round_double(double x)
{
	short	sign;

	sign = 1;
	if (x < 0)
	{
		x = -x;
		sign = -sign;
	}
	double	ones = (int)x;
	double	decimal = x - ones;
	if (decimal >= 0.5)
		return (ones + 1) * sign;
	return ones * sign;
}

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
		printf("bounds: %d\tx: %d\nline.a: %f\tline.a2: %f\tline.dy: %f\tline.dx: %f\n", fdf->image->width, x_pixel, line->a, line->a2, line->dy, line->dx);
		printf("bounds: %d\ty: %d\n", fdf->image->height, y_pixel);
		return (-1);
	}
	return (0);
}

int	ft_abs_int(int ret)
{
	if (ret < 0)
		return -ret;
	return ret;
}

static void	fdf_draw_line(t_fdf *fdf, const t_point *p0, const t_point *p1)
{
	t_line	line;
	int		i;

	fdf_line_init(&line, p0, p1);
	i = 0;
	bool	check = true;
	while (((line.xi != round_double(p1->x)) || line.yi != round_double(p1->y)) && i < 100000)
	{
		fdf_draw_point(fdf, &line);
		if (check)
			line.a2 = line.a * 2;
		check = false;
		if (line.a2 < line.dx && line.yi != round_double(p1->y))
		{
			line.a += line.dx;
			line.yi += line.sy;
			check = true;
		}
		if (line.a2 > -line.dy && line.xi != round_double(p1->x))
		{
			line.a -= line.dy;
			line.xi += line.sx;
			check = true;
		}
		i++;
	}
	if (i == 100000)
	{
		if (line.xi != round_double(p1->x))
			printf("Condition 1: %f %f %i %i %f\n\n\n", line.a2, line.dy, line.sx, line.xi, p1->x);
		if (line.yi != round_double(p1->y))
			printf("Condition 2: %f %f %i %i %d\n\n\n", line.a2, line.dx, line.sy, line.yi, round_double(p1->y));
	}
	fdf_draw_point(fdf, &line);
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
