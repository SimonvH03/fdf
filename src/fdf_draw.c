/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/09 20:32:21 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// victim #1: replaced by map_iteration version

// void
// 	fdf_draw(
// 		void *param)
// {
// 	t_fdf	*fdf;
// 	int		y;
// 	int		x;

// 	fdf = param;
// 	if (fdf->redraw == false)
// 		return ;
// 	draw_background(fdf->image, C_BACKGROUND);
// 	y = 0;
// 	while (y < fdf->map->y_max)
// 	{
// 		x = 0;
// 		while (x < fdf->map->x_max)
// 		{
// 			fdf_draw_down_and_to_the_right(fdf, y, x);
// 			x++;
// 		}
// 		y++;
// 	}
// 	fdf->redraw = false;
// }
