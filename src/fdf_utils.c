/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/03/18 01:59:25 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// used by fdf_init(), keyhook() and user_input_presets.c
// puts the 'origin' back into the middle of the window
void
	fdf_center_offset(
		t_fdf *fdf)
{
	fdf->center.x = fdf->image->width / 2;
	fdf->center.y = fdf->image->height / 2;
	fdf->offset.x = 0;
	fdf->offset.y = 0;
}
