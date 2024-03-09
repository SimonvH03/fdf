/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/09 19:28:06 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from fdf_draw.c, menu_draw.c
void
	draw_background(
		mlx_image_t	*image,
		uint32_t	colour)
{
	uint32_t	i;
	uint32_t	j;

	j = 0;
	while (j < image->height)
	{
		i = 0;
		while (i < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, i, j, colour);
			i++;
		}
		j++;
	}
}

// first we need a margin, don't calculate if x or y is within 'dark square';
//;dark square has half side lengths equal to radius / sqrt(2)
// then we use pythagoras' theorum to see if x,y falls within the horizon
// cases:
// if both points are over the horizon; return (1)
// if both points are outside the horizon; return (0)
// if only one point is over the horizon;
//;malloc a new point (with colour) exactly on the horizon and return (0)
int
	over_the_horizon(
		t_fdf	*fdf,
		t_line	*line)
{
	if (fdf->ballin == false)
		return (0);
	if (line->p0->z < 0 && line->p1->z < 0)
	{
		return (1);
	}
	return (0);
}
