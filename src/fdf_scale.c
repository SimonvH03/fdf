/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/03/18 01:57:55 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from project.c / project()
void
	fdf_scale(
		void *param,
		int y,
		int x)
{
	const t_fdf	*fdf = param;
	t_point	*point;

	point = &fdf->map->project[y][x];
	point->x *= fdf->scale.diff;
	point->y *= fdf->scale.diff;
	point->z *= fdf->scale.diff;
}
