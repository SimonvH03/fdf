/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iteration.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:47:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/26 21:01:35 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// used by map_init(), project(), keyhook(), draw() and user_inputs_presets.c
// applies the function *f(whatever) to the whole map(s)
void
	map_iteration(
		t_map *map,
		mapi_func *function,
		void *param)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			function(param, y, x);
			x++;
		}
		y++;
	}
}

// CHECKLIST
// void	fdf_draw(t_fdf *fdf);
// void	fdf_colour(t_fdf *fdf);
// void	fdf_project_optimized(t_fdf *fdf);
// void	fdf_project(t_fdf *fdf);
// void	fdf_scale(t_fdf *fdf);
// void	map_set_original(t_map *map);
// void	map_fill_polar(t_map *map);
// void	map_set_polar(t_map *map);
// void	map_find_z_min_max(t_map *map);
// get destroyed lol
