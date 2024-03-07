/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/07 19:00:41 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from function fdf_init()
static void
	fdf_scale_init(
		t_fdf	*fdf)
{
	double	scalefinder;

	fdf->scale.initial = fdf->image->width / fdf->map->x_max;
	scalefinder = fdf->image->height / fdf->map->y_max;
	if (scalefinder < fdf->scale.initial)
		fdf->scale.initial = scalefinder;
	fdf->scale.initial *= DEFAULT_SCALE;
	fdf->scale.diff = fdf->scale.initial;
	fdf->scale.total= 1;
}

// from file main.c
int
	fdf_init(
		t_fdf	*fdf,
		t_map	*map)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (fdf->mlx == NULL)
		return (EXIT_FAILURE);
	fdf->image = mlx_new_image(fdf->mlx, WIDTH - MENU_WIDTH, HEIGHT);
	if (fdf->image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(fdf->mlx, fdf->image, MENU_WIDTH, 0) < 0)
		return (EXIT_FAILURE);
	fdf->menu_image = mlx_new_image(fdf->mlx, MENU_WIDTH, HEIGHT);
	if (fdf->menu_image == NULL)
		return (EXIT_FAILURE);
	fdf->map = map;
	fdf->perspective = (t_perspective){ISO_ALPHA, ISO_BETA, ISO_GAMMA, true};
	fdf->precalc = (t_precalc){0, 0, 0, true};
	fdf->speed = ROTATION_SPEED;
	fdf->cosin = (t_cosin){cos(fdf->speed), sin(fdf->speed)};
	fdf_scale_init(fdf);
	fdf_center_offset(fdf);
	fdf->spinlock = false;
	fdf->redraw = true;
	fdf->ballin = false;
	return (EXIT_SUCCESS);
}

// from file fdf_draw.c
void
	fdf_line_init(
		t_line	*line,
		t_map	*map,
		const t_point	*p0,
		const t_point	*p1)
{
	line->map = map;
	line->d_ctl = ft_abs(p1->x - p0->x);
	line->d_pas = ft_abs(p1->y - p0->y);
	line->s_ctl = ft_sign(p1->x - p0->x);
	line->s_pas = ft_sign(p1->y - p0->y);
	line->p0 = p0;
	line->p1 = p1;
	line->i = 0;
	line->j = 0;
	line->err = line->d_pas - line->d_ctl - line->s_ctl;
}
