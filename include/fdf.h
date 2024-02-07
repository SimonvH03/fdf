/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/07 02:13:28 by simon            ###   ########.fr       */
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

//structs_free
void				map_free(t_map *map);

void				map_fill_content(t_map *map);
void				map_project(t_map *map, t_perspective *perspective);

//test_utils
void				check_map_result(t_map *map, const char *str, const char c);

#endif