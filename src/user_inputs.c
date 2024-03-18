/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/18 02:11:49 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void
	fdf_redraw(
		t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_C))
		fdf->redraw = true;
	if (fdf->perspective.reproject
		|| fdf->precalc.reproject
		|| fdf->scale.diff != 1)
		fdf->redraw = true;
}

// using only negative and positive because manual
//;rotations are done with precalculated values
static void
	manual_rotation(
		t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->precalc.gamma = +fdf->precalc.sign;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->precalc.gamma = -fdf->precalc.sign;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->precalc.beta = -fdf->precalc.sign;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->precalc.beta = +fdf->precalc.sign;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->precalc.alpha = -fdf->precalc.sign;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->precalc.alpha = +fdf->precalc.sign;
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
		fdf->offset.y -= 10 * fdf->precalc.sign;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->offset.y += 10 * fdf->precalc.sign;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->offset.x -= 10 * fdf->precalc.sign;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->offset.x += 10 * fdf->precalc.sign;
}

// because bigger maps are slow, press + to get somewhere quick
static void
	inputs_variable_speed(
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

// from main.c loop_hooks()
// do 'em all at once, doesn't matter
void
	user_inputs(
		void	*param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_I))
		input_presets_flat(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_U))
		input_presets_balls(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		inputs_variable_speed(fdf);
	manual_rotation(fdf);
	manual_translation(fdf);
	fdf_redraw(fdf);
}
