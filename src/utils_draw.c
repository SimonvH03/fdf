/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/06 20:16:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int
	over_the_horizon(
		t_fdf	*fdf,
		t_point	*p0,
		t_point	*p1)
{
	if (fdf->ballin == false)
		return (0);
	if (p0->z < 0 || p1->z < 0)
	{
		if (1)
			return (0);
		else
			return (1);
	}
	return (0);
}

// from fdf_draw.c, menu_draw.c
void
	draw_background(
		mlx_image_t	*image,
		uint32_t	colour)
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
