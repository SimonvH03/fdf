/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/15 19:22:13 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from function fdf_init()
static void
	fdf_scale_init(
		t_fdf	*fdf)
{
	double	scalefinder;

	fdf->scale.initial = (double)fdf->image->width / (double)fdf->map->x_max;
	scalefinder = (double)fdf->image->height / (double)fdf->map->y_max;
	if (scalefinder < fdf->scale.initial)
		fdf->scale.initial = scalefinder;
	fdf->scale.initial *= DEFAULT_SCALE;
	if (fdf->scale.initial == 0)
		fdf->scale.initial = 0.1;
	fdf->scale.diff = fdf->scale.initial;
	fdf->scale.total = 1;
	if (fdf->map->radius == 0)
		fdf->scale.sphere = 1;
	else
		fdf->scale.sphere = fdf->image->width / (2.2 * fdf->map->radius) * DEFAULT_SCALE;
}

int
	map_init(
		t_map	*map,
		char	*map_name)
{
	map->original = NULL;
	map->project = NULL;
	map->polar = NULL;
	map->palette = (t_palette)
			{P_RGB_NR, C_RGB_BACK,
			C_RGB_LOW, C_RGB_MID, C_RGB_HIGH};
	if (map_is_globe(map_name) == EXIT_SUCCESS)
		map->palette = (t_palette){P_EARTH_NR, C_EARTH_BACK, 0, 0, 0};
	map->name = map_name;
	map->fd = 0;
	if (map_read(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map->z_min = 0;
	map->z_max = 0;
	map_iteration(map, &map_find_z_min_max, map);
	map->total_height = map->z_max - map->z_min;
	map->radius = (map->total_height) * 10;
	map->shape = (t_shape)
			{S_FULL_SPHERE, -2 * PI / (map->x_max), PI / (map->y_max - 1)};
	map_iteration(map , &map_colour, map);
	map_iteration(map, &map_fill_polar, map);
	return (EXIT_SUCCESS);
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
	fdf->radius = fdf->map->radius;
	fdf->darksquare = fdf->radius / sqrt(2);
	fdf_center_offset(fdf);
	fdf->spinlock = false;
	fdf->redraw = true;
	fdf->ballin = false;
	return (EXIT_SUCCESS);
}

bool
	line_swap_control_passive(
		t_line *line)
{
	int	temp;

	if (line->d_ctl >= line->d_pas)
		return (false);
	temp = line->d_ctl;
	line->d_ctl = line->d_pas;
	line->d_pas = temp;
	temp = line->s_ctl;
	line->s_ctl = line->s_pas;
	line->s_pas = temp;
	return (true);
}

// from file fdf_draw.c
void
	fdf_line_init(
		t_line			*line,
		const t_point	*p0,
		const t_point	*p1)
{
	line->d_ctl = ft_abs(p1->x - p0->x);
	line->d_pas = ft_abs(p1->y - p0->y);
	line->s_ctl = ft_sign(p1->x - p0->x);
	line->s_pas = ft_sign(p1->y - p0->y);
	line->swapped = line_swap_control_passive(line);
	line->p0 = p0;
	line->p1 = p1;
	line->i = 0;
	line->j = 0;
	line->err = line->d_pas - line->d_ctl - line->s_ctl;
}
