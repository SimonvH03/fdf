/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/05 18:09:42 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static uint32_t	fdf_colour(t_fdf *fdf, t_line *line)
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
			fdf_draw_full(fdf, x, y);
			x++;
		}
		y++;
	}
	fdf->redraw = false;
	// fdf_draw_point(fdf, &(t_line){0, 0, 0, 0, 0, 0, 0, 0, 0});
}
