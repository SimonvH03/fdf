/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/06 18:38:01 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static uint32_t
	fdf_line_colour(
		t_fdf *fdf,
		t_line *line)
{
	return (Z_LOW);
}

void
	fdf_draw_point(
		t_fdf *fdf,
		t_line *line)
{
	int	x_pixel;
	int	y_pixel;

	x_pixel = (line->i * line->s_ctl) + line->p0->x + fdf->x_offset;
	y_pixel = (line->j * line->s_pas) + line->p0->y + fdf->y_offset;
	if ((x_pixel < (int)fdf->image->width && y_pixel < (int)fdf->image->height
			&& x_pixel > 0 && y_pixel > 0)
		&& !(fdf->ballin && (line->p0->z < 0 || line->p1->z < 0)))
	{
		mlx_put_pixel(fdf->image, x_pixel, y_pixel,
			fdf_line_colour(fdf, line));
	}
}

void
	fdf_draw(
		void *param)
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
}
