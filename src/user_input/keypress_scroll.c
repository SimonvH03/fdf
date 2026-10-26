/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keypress_scroll.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2026/10/24 17:42:02 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// from main.c / loop_hooks()
void
	keyhook(
		mlx_key_data_t keydata,
		void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		fdf->spin_lock = (!fdf->spin_lock);
		precalc(fdf);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf_center_offset(fdf);
		fdf->scale.diff = 1 / fdf->scale.total;
		fdf->scale.total = 1;
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		map_cycle_palettes(fdf->map);
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		fdf->step.sign *= -1;
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
		fdf->horizon = !fdf->horizon;
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		map_toggle_squish(fdf);
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
	{
		fdf->scroll_behaviour = (fdf->scroll_behaviour + 1) % (t_scroll)max;
		if (fdf->scroll_behaviour == (t_scroll)move
			|| fdf->scroll_behaviour == (t_scroll)rotate)
			ft_swap(&fdf->speed, &fdf->alt_speed, sizeof(fdf->speed));
	}
}

void
	scroll_move(
		t_fdf *fdf,
		double xdelta,
		double ydelta)
{
	if (xdelta)
		fdf->offset.x += fdf->step.sign * (xdelta * fdf->speed);
	if (ydelta)
		fdf->offset.y += fdf->step.sign * (ydelta * fdf->speed);
}

void
	scroll_zoom(
		t_fdf *fdf,
		double ydelta)
{
	if (ydelta)
	{
		fdf->scale.diff *= 1 + (ydelta / 10);
		fdf->scale.total *= 1 + (ydelta / 10);
	}
}

void
	scroll_squish(
		t_fdf *fdf,
		double ydelta)
{
	if (ydelta)
		fdf->squish_factor *= pow(1.1, 1 + ydelta);
}

// from main.c / loop_hooks()
void
	scrollhook(
		double xdelta,
		double ydelta,
		void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (fdf->scroll_behaviour != (t_scroll)move)
		(void)xdelta;
	switch (fdf->scroll_behaviour)
	{
		case (t_scroll)move:
			scroll_move(fdf, xdelta, ydelta);
			break;
		case (t_scroll)zoom:
			scroll_zoom(fdf, ydelta);
			break;
		case (t_scroll)squish:
			scroll_squish(fdf, ydelta);
			break;
		case (t_scroll)max:
			break;
	}
}
