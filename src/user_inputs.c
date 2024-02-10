/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/10 01:06:31 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	user_inputs(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->perspective->alpha = -ROTATION_SPEED;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->perspective->alpha = ROTATION_SPEED;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->perspective->beta = -ROTATION_SPEED;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->perspective->beta = ROTATION_SPEED;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->perspective->gamma = -ROTATION_SPEED;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->perspective->gamma = ROTATION_SPEED;
}
