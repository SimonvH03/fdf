/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/07 22:09:28 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <MLX42/MLX42.h>
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
// for printf, exclude later
# include <stdio.h>

// mlx window
# define WIDTH 1024
# define HEIGHT 1024

// colours
# define C_LINES 0xFFFFFFFF
# define C_BACKGROUND 0x00000000

# define PI 3.14159265

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	uint32_t		colour;
}	t_point;

// free: map.content (free2d)
// no free: map.name = argv[1]
typedef struct s_map
{
	t_point			**content;
	int				fd;
	char			*name;
	int				x_max;
	int				y_max;
}	t_map;

typedef struct s_perspective
{
	double			alpha;
	double			beta;
	double			gamma;
}	t_perspective;

// free: fdf.map->content
typedef struct s_fdf
{
	t_map			*map;
	mlx_image_t		*image;
	mlx_t			*mlx;
	t_perspective	*perspective;
}	t_fdf;


// main
void			*fdf_init(t_fdf *fdf);
void			map_read(t_map *map);

// loops
void			map_project(void *param);
void			fdf_draw(void *param);

// utils
void			map_free(t_map *map);
double			rad(double angle_deg);

//test_utils
void			check_map_result(t_map *map, const char *str, const char *v);

#endif