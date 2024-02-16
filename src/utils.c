/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/16 15:07:37 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// turn degree angle into radial for stupid math.h functions
double	rad(double angle_deg)
{
	const double	ratio = 180 / PI;

	return (angle_deg / ratio);
}

// content is malloc'd and should be free'd
void	map_free(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->y_max && map->project[i])
		free(map->project[i++]);
	free(map->project);
	i = 0;
	while (i < map->y_max && map->original[i])
		free(map->original[i++]);
	free(map->original);
}

// set all point coordinates to original values
void	map_project_reset(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			map->project[y][x] = map->original[y][x];
			x++;
		}
		y++;
	}
}

void	fdf_scale_init(t_fdf *fdf)
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

void	draw_background(mlx_image_t *image, uint32_t colour)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, x, y, colour);
			x++;
		}
		y++;
	}
}

// print resized window dimensions to stdoutput
// static void	ft_resize(void *param)
// {
// 	mlx_t			*mlx;
// 	static int32_t	previous_width;
// 	static int32_t	previous_height;

// 	mlx = param;
// 	if (mlx_is_key_down((mlx_t *)mlx, MLX_KEY_ESCAPE))
// 	{
// 		printf("%s", "\e[33mESC pressed\n\e[31m:closing window\n");
// 		mlx_close_window((mlx_t *)mlx);
// 	}
// 	if (mlx->width != previous_width || mlx->height != previous_height)
// 	{
// 		printf("\e[33mresized\n\e[0m:W: %d H: %d\n", mlx->width, mlx->height);
// 		previous_width = mlx->width;
// 		previous_height = mlx->height;
// 	}
// }
