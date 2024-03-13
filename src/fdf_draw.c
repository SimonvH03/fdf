/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/11 19:26:08 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	fdf_draw(
		void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (fdf->redraw == false)
		return ;
	draw_background(fdf->image, fdf->map->palette.background);
	map_iteration(fdf->map, &fdf_draw_down_and_to_the_right, fdf);
	fdf->redraw = false;
}
