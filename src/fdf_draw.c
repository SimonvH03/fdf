/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/28 23:54:03 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t	fdf_colour(t_fdf *fdf, t_line *line)
{
	// int	diff;

	// if (line->d_ctl > line->d_pas)
	// 	diff = (int)(100 * (line->d_ctl - line->i) / line->d_ctl);
	// else
	// 	diff = (int)(100 * (line->d_pas - line->j) / line->d_pas);
	(void)fdf;
	(void)line;
	return (C_WHITE);
}

void	fdf_draw_point(t_fdf *fdf, t_line *line)
{
	int	x_pixel;
	int	y_pixel;

	x_pixel = (line->i * line->s_ctl) + line->x0 + fdf->x_offset;
	y_pixel = (line->j * line->s_pas) + line->y0 + fdf->y_offset;
	if (x_pixel < (int)fdf->image->width && y_pixel < (int)fdf->image->height
		&& x_pixel > 0 && y_pixel > 0)
	{
		mlx_put_pixel(fdf->image, x_pixel, y_pixel, fdf_colour(fdf, line));
	}
	// else
	// {
	// 	printf("CHECK FAILED\nbounds:\t(%d, %d)\t(%d, %d)\n",
	// 	fdf->image->width, fdf->image->height, x_pixel, y_pixel);
	// }
}

int	fdf_straight_line(t_fdf *fdf, t_line *line)
{
	if (line->d_ctl == 0)
	{
		while (line->j <= line->d_pas)
		{
			fdf_draw_point(fdf, line);
			line->j++;
		}
		return (0);
	}
	if (line->d_pas == 0)
	{
		while (line->i <= line->d_ctl)
		{
			fdf_draw_point(fdf, line);
			line->i++;
		}
		return (0);
	}
	return (1);
}

int	fdf_draw_line(t_fdf *fdf, t_point *p0, t_point *p1)
{
	t_line	line;

	fdf_line_init(&line, p0, p1);
	if (fdf_straight_line(fdf, &line))
	{
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
	return (0);
}

int	fdf_checkpoint(t_fdf *fdf, int x_pixel, int y_pixel)
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

void	fdf_check_line(t_fdf *fdf, int x, int y)
{
	t_point *p0;
	t_point *p1;
	int		bound0;
	int		bound1;

	p0 = &fdf->map->project[y][x];
	bound0 = fdf_checkpoint(fdf, p0->x, p0->y);
	if (fdf->ballin && (x + 1) == fdf->map->x_max)
	{
		p1 = &fdf->map->project[y][0];
		bound1 = fdf_checkpoint(fdf, p1->x, p1->y);
		if (!bound0 || !bound1)
			fdf_draw_line(fdf, p0, p1);
	}
	if ((x + 1) < fdf->map->x_max)
	{
		p1 = &fdf->map->project[y][x + 1];
		bound1 = fdf_checkpoint(fdf, p1->x, p1->y);
		if (!bound0 || !bound1)
			fdf_draw_line(fdf, p0, p1);
	}
	if ((y + 1) < fdf->map->y_max)
	{
		p1 = &fdf->map->project[y + 1][x];
		bound1 = fdf_checkpoint(fdf, p1->x, p1->y);
		if (!bound0 || !bound1)
			fdf_draw_line(fdf, p0, p1);
	}
}

void	fdf_draw(void *param)
{
	t_fdf	*fdf;
	int		y;
	int		x;

	fdf = param;
	if (fdf->redraw == false)
		return ;
	draw_background(fdf->image, C_BACKGROUND);
	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			// if ((x + 1) < fdf->map->x_max)
			// 	fdf_draw_line(fdf, &fdf->map->project[y][x],
			// 		&fdf->map->project[y][x + 1]);
			// if ((y + 1) < fdf->map->y_max)
			// 	fdf_draw_line(fdf, &fdf->map->project[y][x],
			// 		&fdf->map->project[y + 1][x]);;
			fdf_check_line(fdf, x, y);
			x++;
		}
		y++;
	}
	fdf->redraw = false;
}

// void	fdf_draw_line(t_fdf *fdf, t_point *p0, t_point *p1)
// {
// 	// printf("%d\n", line.d_control - line.d_passive);
// 	// fdf_draw_point(fdf, &line, 0, 0);
// 	// fdf_draw_point(fdf, &line, 0, line.d_passive * line.s_passive);
// 	// fdf_draw_point(fdf, &line, line.d_control * line.s_control, 0);
// 	// fdf_draw_point(fdf, &line, line.d_control * line.s_control, line.d_passive * line.s_passive);
// }