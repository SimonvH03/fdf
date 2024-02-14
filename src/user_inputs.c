/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/14 19:33:32 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	input_presets(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
	{
		map_project_reset(fdf->map);
		fdf->spinlock = false;
		fdf->scalediff = fdf->init_scale;
		fdf->scale = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		map_project_reset(fdf->map);
		*fdf->perspective = (t_perspective){ISO_ALPHA, ISO_BETA, ISO_GAMMA};
		fdf->spinlock = false;
		fdf->scalediff = fdf->init_scale;
		fdf->scale = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_M))
	{
		fdf->scalediff = 1 / fdf->scale;
		printf ("scalediff = %f\n", fdf->scalediff);
		fdf->scale = 1;
	}
}

static void	manual_rotation(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->perspective->alpha -= fdf->speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->perspective->alpha += fdf->speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->perspective->beta += fdf->speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->perspective->beta -= fdf->speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->perspective->gamma -= fdf->speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->perspective->gamma += fdf->speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

void	user_inputs(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_I)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_M))
		input_presets(fdf);
	manual_rotation(fdf);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		fdf->spinlock = (!fdf->spinlock);
	if (fdf->spinlock)
		fdf->speed = ROTATION_SPEED / 100;
	else
		fdf->speed = ROTATION_SPEED;
}

void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	fdf->scalediff += ydelta / 20;
	fdf->scale = fdf->scale + (fdf->scalediff - 1) * fdf->scale;
	printf("scale(%f) += scalediff(%f)\n", fdf->scale, fdf->scalediff);
}
