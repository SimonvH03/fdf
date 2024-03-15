/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/15 18:33:04 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from fdf_draw.c, menu_draw.c
void
	draw_background(
		const mlx_image_t *image,
		const uint32_t colour)
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

void
	line_swap_points(
		t_line *line)
{
	t_point	*temp;

	temp = (t_point *)line->p0;
	line->p0 = line->p1;
	line->p1 = temp;
	line->s_ctl *= -1;
	line->s_pas *= -1;
}
