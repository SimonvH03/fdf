/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/04 12:12:36 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include <unistd.h>
#include <fcntl.h>

#define WIDTH 1024
#define HEIGHT 1024
#define DELIMITER ' '

typedef struct s_point
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	z;
}	t_point;

typedef struct s_lineseg
{
	t_point		*point0;
	t_point		*point1;
	uint32_t	dy_dx;
	uint32_t	xi;
	uint32_t	colour;
}	t_lineseg;

typedef struct s_mapfdf
{
	char		*name;
	int			fd;
}	t_mapfdf;

typedef struct s_wireframe
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_wireframe;

void	wireframe_create(void *param);
t_point	*read_point(t_mapfdf *mapfdf);