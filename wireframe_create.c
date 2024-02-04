/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/04 12:14:01 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	wireframe_create(void *param)
{
	mlx_image_t	*image;
	t_point		*point;
	t_wireframe	*wireframe;

	wireframe = param;
	//check_map
	point = read_point(wireframe);
	//
}

t_point	*read_point(t_mapfdf *mapfdf)
{
	t_point	point;

	mapfdf->fd = open(mapfdf->name, O_RDONLY);

	return (&point);
}

int	main(void)
{

}