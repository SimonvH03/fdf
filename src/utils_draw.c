/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/08 19:19:29 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

	// printf("p0: %p | (%f, %f, %f)\n", line->p0, line->p0->x, line->p0->y, line->p0->z);
	// printf("p1: %p | (%f, %f, %f)\n", line->p1, line->p1->x, line->p1->y, line->p1->z);
int
	over_the_horizon(
		t_fdf	*fdf,
		t_line	*line)
{
	if (fdf->ballin == false)
		return (0);
	if (line->p0->z < 0 && line->p1->z < 0)
	{

		// pythagoras(fdf->map, line->p0);
		// pythagoras(fdf->map, line->p1);
	
		return (1);
	}
	return (0);
}
