/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/23 19:24:36 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from function fdf_init()
static void	fdf_scale_init(t_fdf *fdf)
{
	double	scaley;

	fdf->init_scale = fdf->image->width / fdf->map->x_max;
	scaley = fdf->image->height / fdf->map->y_max;
	if (scaley < fdf->init_scale)
		fdf->init_scale = scaley;
	fdf->init_scale *= 0.5;
	fdf->scalediff = fdf->init_scale;
	fdf->scale = 1;
	printf ("init_scale: %f\n", fdf->scalediff);
}

// from file main.c
int	fdf_init(t_fdf *fdf, t_map *map, t_perspective *perspective)
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
	fdf->perspective = perspective;
	fdf_scale_init(fdf);
	fdf->x_offset = fdf->image->width / 2;
	fdf->y_offset = fdf->image->height / 2;
	fdf->spinlock = false;
	fdf->speed = ROTATION_SPEED;
	fdf->redraw = true;
	return (EXIT_SUCCESS);
}

// from file fdf_draw.c
void	fdf_line_init(t_line *line, const t_point *p0, const t_point *p1)
{
	line->d_ctl = ft_abs(p1->x - p0->x);
	line->d_pas = ft_abs(p1->y - p0->y);
	line->s_ctl = ft_sign(p1->x - p0->x);
	line->s_pas = ft_sign(p1->y - p0->y);
	line->x0 = p0->x;
	line->y0 = p0->y;
}