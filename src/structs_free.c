/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/06 10:58:35 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	map_free(t_map *map)
{
	int	i;

	i = 0;
	while (map->content[i])
		free(map->content[i++]);
	free(map->content);
}

void	fdf_free(t_fdf *fdf)
{
	free(fdf->image);
	free(fdf->map);
	free(fdf->mlx);
}
