/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iteration.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:47:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/09 19:06:14 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// this function applies the function *f(whatever) to the whole map(s)
void
	map_iteration(t_map *map, void (*f)(void *param))
	{

	}


void	fdf_draw(void *param);
void	fdf_colour(t_fdf *fdf);
void	fdf_project_optimized(t_fdf *fdf);
void	fdf_project(t_fdf *fdf);
void	fdf_scale(t_fdf *fdf);
void	map_set_original(t_map *map);
void	map_fill_polar(t_map *map);
void	map_set_polar(t_map *map);
void	map_find_z_min_max(t_map *map);