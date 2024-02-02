/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/02 20:02:54 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>

#define WIDTH 1024
#define HEIGHT 1024

void	wireframe_create(void *param);

typedef struct s_point
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	z;
}	t_point;

typedef struct s_wireframe
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_wireframe;
