/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/14 17:27:44 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "MLX42/MLX42.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
// for printf, exclude later
# include <stdio.h>

# define PI 3.14159265

// mlx window
# define WINDOW_TITLE "fdf"
# define WIDTH 1600
# define HEIGHT 1600

// fdf defaults
# define ISO_GAMMA rad(-45)
# define ISO_BETA 0
# define ISO_ALPHA rad(-35.264)

// user input
# define ROTATION_SPEED 0.01745329

// colours
# define C_LINES 0xFFFFFFFF
# define C_BACKGROUND 0xFF000020

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
	t_point			**project;
	t_point			**original;
	char			*name;
	int				fd;
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
	double			scale;
	double			scalecum;
	double			scalediff;
	double			x_origin;
	double			y_origin;
	bool			spinlock;
	double			speed;
}	t_fdf;

// main
void			map_read(t_map *map);

// loops
void			keyhook(mlx_key_data_t keydata, void *param);
void			scrollhook(double xdelta, double ydelta, void *param);
void			user_inputs(void *param);
void			map_scale(void *param);
void			map_project(void *param);
void			fdf_draw(void *param);

// utils
double			rad(double angle_deg);
void			map_project_reset(t_map *map);
void			fdf_scale_init(t_fdf *fdf);
void			map_free(t_map *map);

//test_utils
void			check_map_result(t_map *map, const char *str, const char *v);

#endif