/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cycle_stuff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:05:29 by simon             #+#    #+#             */
/*   Updated: 2024/03/11 00:49:51 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_palette	cycle_palettes(t_map *map)
{
	if (map->palette.nr == P_RGB_NR)
		return ((t_palette)
			{P_METAL_NR, C_METAL_BACK,
			C_METAL_LOW, C_METAL_MID, C_METAL_HIGH});
	else if (map->palette.nr == P_METAL_NR)
		return ((t_palette)
			{P_PASTEL_NR, C_PASTEL_BACK,
			C_PASTEL_LOW, C_PASTEL_MID, C_PASTEL_HIGH});
	else if (map->palette.nr == P_PASTEL_NR)
		return ((t_palette)
			{P_EARTH_NR, C_EARTH_BACK,
			0, 0, 0});
	else
		return ((t_palette)
			{P_RGB_NR, C_RGB_BACK,
			C_RGB_LOW, C_RGB_MID, C_RGB_HIGH});
}
