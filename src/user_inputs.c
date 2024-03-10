/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/10 02:07:52 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void
	manual_rotation(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->precalc.alpha = -1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->precalc.alpha = +1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->precalc.beta = +1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->precalc.beta = -1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->precalc.gamma = -1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->precalc.gamma = +1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (fdf->precalc.gamma
		|| fdf->precalc.beta
		|| fdf->precalc.alpha)
		fdf->precalc.reproject = true;
}

static void
	manual_translation(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->offset.y += 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->offset.y -= 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->offset.x += 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->offset.x -= 10;
}

static void
	input_variable_speed(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
	{
		if (fdf->speed > 0.00001)
			fdf->speed *= 0.95;
		fdf->cosin = (t_cosin){cos(fdf->speed), sin(fdf->speed)};
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
	{
		if (fdf->speed < PI)
			fdf->speed *= 1.05;
		else
			fdf->speed = ROTATION_SPEED;
		fdf->cosin = (t_cosin){cos(fdf->speed), sin(fdf->speed)};
	}
}

void
	user_inputs(
		void	*param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_I)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_O))
		input_presets_1(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_M)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_N))
		input_presets_2(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		input_variable_speed(fdf);
	// if (mlx_is_key_down(fdf->mlx, MLX_KEY_C))
	manual_rotation(fdf);
	manual_translation(fdf);
	fdf_redraw(fdf);
}
