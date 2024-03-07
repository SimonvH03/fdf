/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/07 15:13:33 by simon            ###   ########.fr       */
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
# define WIDTH 1200
# define HEIGHT 800
# define MENU_WIDTH 400
// # define WIDTH 2000
// # define HEIGHT 1600
// # define MENU_WIDTH 400

// fdf defaults
# define DEFAULT_SCALE 0.7

// rotation defaults
// # define ISO_GAMMA 0
# define ISO_GAMMA deg_to_rad(-45)
# define ISO_BETA 0
// # define ISO_ALPHA 0
# define ISO_ALPHA deg_to_rad(-35.264)

// user input
# define ROTATION_SPEED 0.01

// colours
# define C_WHITE 0xFFFFFFFF
# define C_BACKGROUND 0x000000FF
# define C_MENU 0xFF000040
# define Z_LOW 0xFF000088
# define Z_MID 0x00FF0088
# define Z_HIGH 0x0000FF88

typedef struct s_colour
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour;

typedef struct s_cosin
{
	double	a_cos;
	double	a_sin;
}	t_cosin;

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	uint32_t		colour;
}	t_point;

// free: map->content, map->project, map->polar
// no free: map->name = argv[1]
typedef struct s_map
{
	t_point			**original;
	t_point			**project;
	t_point			**polar;
	char			*name;
	int				fd;
	int				x_max;
	int				y_max;
	int				z_min;
	int				z_max;
	int				radius;
}	t_map;

typedef struct s_line
{
	int				d_ctl;
	int				d_pas;
	int				s_ctl;
	int				s_pas;
	int				err;
	int				i;
	int				j;
	const t_point	*p0;
	const t_point	*p1;
	t_map			*map;
}	t_line;

typedef struct s_precalc
{
	short			alpha;
	short			beta;
	short			gamma;
	bool			reproject;
}	t_precalc;

typedef struct s_perspective
{
	double			alpha;
	double			beta;
	double			gamma;
	bool			reproject;
}	t_perspective;

typedef struct s_scale
{
	double			diff;
	double			total;
	double			initial;
}	t_scale;

typedef struct s_offset
{
	int				x;
	int				y;
}	t_offset;

typedef struct s_fdf
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*menu_image;
	t_map			*map;
	t_perspective	perspective;
	t_precalc		precalc;
	t_cosin			cosin;
	t_scale			scale;
	t_offset		offset;
	double			speed;
	bool			spinlock;
	bool			redraw;
	bool			ballin;
}	t_fdf;

// main
int			map_read(t_map *map);
void		menu_draw(t_fdf *fdf);

// map_mods.c
void		map_fill_polar(t_map *map);
void		map_set_polar(t_map *map);
void		map_set_original(t_map *map);

// loops
void		keyhook(mlx_key_data_t keydata, void *param);
void		scrollhook(double xdelta, double ydelta, void *param);
void		user_inputs(void *param);
void		fdf_scale_and_project(void *param);
void		fdf_draw(void *param);

// fdf_projects
void		fdf_project(t_fdf *fdf);
void		fdf_project_optimized(t_fdf *fdf);

// utils_fdf.c
void		fdf_redraw(t_fdf *fdf);
void		fdf_scale(t_fdf *fdf);
void		fdf_center_offset(t_fdf *fdf);

// user_inputs_presets.c
void		input_presets_1(t_fdf *fdf);
void		input_presets_2(t_fdf *fdf);

// utils_calc.c
double		deg_to_rad(double angle_deg);
double		rad_to_deg(double angle_rad);
double		ft_abs(double val);
short		ft_sign(double val);

// utils_init.c
int			fdf_init(t_fdf *fdf, t_map *map);
void		fdf_line_init(t_line *line, t_map *map,
				const t_point *p0, const t_point *p1);

// utils_map.c
int			map_malloc_y(t_map *map);
int			map_malloc_x(t_map *map, int y);
void		map_find_z_min_max(t_map *map);
void		map_colour(t_map *map);

// utils_misc.c
void		map_free(t_map *map);
void		draw_background(mlx_image_t *image, uint32_t colour);

// fdf_draw.c
void		fdf_draw_point(t_fdf *fdf, t_line *line);
int			fdf_check_point(t_fdf *fdf, int x_pixel, int y_pixel);
void		fdf_draw(void *param);

// fdf_draw_2.c
void		fdf_draw_down_and_to_the_right(t_fdf *fdf, int x, int y);
void		fdf_draw_line(t_fdf *fdf, t_point *p0, t_point *p1);

// utils_draw.c
int			over_the_horizon(t_fdf *fdf, t_line *line);

// utils_test.c
// void		check_map_result(t_map *map, const char *str, const char *v);

#endif