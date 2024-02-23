/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/23 19:47:07 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t	fdf_colour(t_line *line)
{
	(void)line;
	return (C_LINES);
}

static void	fdf_draw_point(t_fdf *fdf, t_line *line, int i, int j)
{
	int	x_pixel;
	int	y_pixel;

	x_pixel = i + line->x0 + fdf->x_offset;
	y_pixel = j + line->y0 + fdf->y_offset;
	if (x_pixel < (int)fdf->image->width && y_pixel < (int)fdf->image->height
		&& x_pixel > 0 && y_pixel > 0)
	{
		mlx_put_pixel(fdf->image, x_pixel, y_pixel, fdf_colour(line));
	}
	// else
	// {
	// 	printf("bounds: (%d, %d)\t(%d, %d)\n",
	// 	fdf->image->width, fdf->image->height, i, j);
	// }
}

static int	fdf_straight_line(t_fdf *fdf, t_line *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line->d_ctl == 0)
	{
		while (j <= line->d_pas)
		{
			fdf_draw_point(fdf, line, i, j * line->s_pas);
			j++;
		}
		return (0);
	}
	if (line->d_pas == 0)
	{
		while (i <= line->d_ctl)
		{
			fdf_draw_point(fdf, line, i * line->s_ctl, j);
			i++;
		}
		return (0);
	}
	return (1);
}

static void	fdf_draw_line(t_fdf *fdf, const t_point *p0, const t_point *p1)
{
	t_line	line;
	int	i;
	int	j;

	fdf_line_init(&line, p0, p1);
	i = 0;
	j = 0;
	line.err = line.d_pas - line.d_ctl - line.s_ctl;
	if (fdf_straight_line(fdf, &line))
	{
		while (i != line.d_ctl)
		{
			fdf_draw_point(fdf, &line, i * line.s_ctl, j * line.s_pas);
			while (line.err >= 0)
			{
				j += 1;
				line.err -= line.d_ctl;
				fdf_draw_point(fdf, &line, i * line.s_ctl, j * line.s_pas);
			}
			i += 1;
			line.err += line.d_pas;
		}
	}
	fdf_draw_point(fdf, &line, i * line.s_ctl, j * line.s_pas);
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
	fdf->redraw = false;
}

// static void	fdf_draw_line(t_fdf *fdf, const t_point *p0, const t_point *p1)
// {
// 	// printf("%d\n", line.d_control - line.d_passive);
// 	// fdf_draw_point(fdf, &line, 0, 0);
// 	// fdf_draw_point(fdf, &line, 0, line.d_passive * line.s_passive);
// 	// fdf_draw_point(fdf, &line, line.d_control * line.s_control, 0);
// 	// fdf_draw_point(fdf, &line, line.d_control * line.s_control, line.d_passive * line.s_passive);
// }