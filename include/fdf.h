/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/23 21:09:48 by svan-hoo         ###   ########.fr       */
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
# define HEIGHT 1200
# define MENU_WIDTH 400

// fdf defaults
# define ISO_GAMMA rad(-45)
# define ISO_BETA 0
# define ISO_ALPHA rad(-35.264)

// user input
# define ROTATION_SPEED 0.01745329

// colours
# define C_WHITE 0xFFFFFFFF
# define C_BACKGROUND 0xFF000020
# define C_MENU 0xFF000040
# define Z_LOW 0x88FFFFFF
# define Z_HIGH 0xFFF88FFF

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
}	t_point;

typedef struct s_line
{
	int			d_ctl;
	int			d_pas;
	int			s_ctl;
	int			s_pas;
	int			err;
	int			i;
	int			j;
	double		x0;
	double		y0;
	int			z0;
	int			z1;
}	t_line;

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
	int				z_min;
	int				z_max;
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
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*menu_image;
	t_map			*map;
	t_perspective	*perspective;
	double			init_scale;
	double			scale;
	double			scalediff;
	double			x_offset;
	double			y_offset;
	bool			spinlock;
	double			speed;
	bool			redraw;
}	t_fdf;

// main
void			map_read(t_map *map);
void			menu_draw(t_fdf *fdf);

// loops
void			keyhook(mlx_key_data_t keydata, void *param);
void			scrollhook(double xdelta, double ydelta, void *param);
void			user_inputs(void *param);
void			map_scale(void *param);
void			map_project(void *param);
void			fdf_draw(void *param);

// utils_calc.c
double			rad(double angle_deg);
double			ft_abs(double val);
short			ft_sign(double val);

// utils_init.c
int				fdf_init(t_fdf *fdf, t_map *map, t_perspective *perspective);
void			fdf_line_init(t_line *line, const t_point *p0, const t_point *p1);

// utils_misc.c
void			map_free(t_map *map);
void			map_project_reset(t_map *map);
void			map_find_z_min_max(t_map *map);
void			draw_background(mlx_image_t *image, uint32_t colour);

// utils_test.c
void			check_map_result(t_map *map, const char *str, const char *v);

#endif