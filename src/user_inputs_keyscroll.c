/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_keyscroll_hooks.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/09 23:07:06 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	keyhook(
		mlx_key_data_t	keydata,
		void			*param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		fdf->spinlock = (!fdf->spinlock);
		fdf->speed = ROTATION_SPEED;
		fdf->cosin = (t_cosin){cos(fdf->speed), sin(fdf->speed)};
	}
}

void
	scrollhook(
		double xdelta,
		double ydelta,
		void	*param)
{
	t_fdf	*fdf;

	fdf = param;
	(void)xdelta;
	if (ydelta)
	{
		fdf->scale.diff *= 1 + (ydelta / 10);
		fdf->scale.total *= 1 + (ydelta / 10);
	}
}
