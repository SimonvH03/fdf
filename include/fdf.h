/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/11 15:52:59 by simon            ###   ########.fr       */
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
// # define WIDTH 1200
// # define HEIGHT 800
// # define MENU_WIDTH 400
# define WIDTH 2000
# define HEIGHT 1600
# define MENU_WIDTH 400

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
# define C_WHITE			0xFFFFFFFF
# define C_GRAY				0x404040FF
# define C_BLACK			0x000000FF
# define C_BACKGROUND		0x20002088
# define C_MENU				0xFF000040

// palette RGB
# define P_RGB_NR			0
# define C_RGB_BACK			C_BLACK
# define C_RGB_LOW			0xFF0000FF
# define C_RGB_MID			0x00FF00FF
# define C_RGB_HIGH			0x0000FFFF

// palette Metal
# define P_METAL_NR			1
# define C_METAL_BACK		C_GRAY
# define C_METAL_LOW		C_BLACK
# define C_METAL_MID		0x808080FF
# define C_METAL_HIGH		C_WHITE

// palette Pastel
# define P_PASTEL_NR		2
# define C_PASTEL_BACK		0xFBEEE0FF
# define C_PASTEL_LOW		0x85D65CFF
# define C_PASTEL_MID		0xFFE840FF
# define C_PASTEL_HIGH		0xFBBBC8FF

// palette Earth
# define P_EARTH_NR			3
# define C_EARTH_BACK		C_BLACK
# define C_EARTH_DEEP_SEA	0x202060FF
# define C_EARTH_SEA		0x303090FF
# define C_EARTH_LAND		0x206020FF
# define C_EARTH_MOUNTAIN	0x483038FF
# define C_EARTH_SNOW		0xBBBBBBFF

# define S_FULL_SPHERE		0
# define S_HALF_SPHERE		1

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	uint32_t		colour;
}	t_point;

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
}	t_line;

typedef struct s_colour_construct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour_construct;

typedef struct s_shape
{
	int				nr;
	double			longitude;
	double			latitude;
}	t_shape;

typedef struct s_palette
{
	int				nr;
	uint32_t		background;
	uint32_t		low;
	uint32_t		mid;
	uint32_t		high;
}	t_palette;

// free: map->content, map->project, map->polar
// no free: map->name = argv[1]
typedef struct s_map
{
	t_point			**original;
	t_point			**project;
	t_point			**polar;
	t_palette		palette;
	char			*name;
	int				fd;
	int				x_max;
	int				y_max;
	t_shape			shape;
	int				z_min;
	int				z_max;
	int				total_height;
	int				radius;
}	t_map;

typedef struct s_perspective
{
	double			alpha;
	double			beta;
	double			gamma;
	bool			reproject;
}	t_perspective;

typedef struct s_precalc
{
	short			alpha;
	short			beta;
	short			gamma;
	bool			reproject;
}	t_precalc;

typedef struct s_cosin
{
	double			a_cos;
	double			a_sin;
}	t_cosin;

typedef struct s_scale
{
	double			diff;
	double			total;
	double			initial;
	double			sphere;
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
	t_offset		center;
	t_offset		offset;
	double			speed;
	bool			spinlock;
	bool			redraw;
	bool			ballin;
}	t_fdf;

// main
int			map_read(t_map *map);
void		menu_draw(t_fdf *fdf);

// map_iteration
void		map_iteration(t_map *map,
				void (*function)(void *param, const int y, const int x),
				void *parameter);

// map_mods.c
void		map_fill_polar(void *param, const int y, const int x);
void		map_set_polar(void *param, const int y, const int x);
void		map_set_original(void *param, const int y, const int x);

// cycle_stuff.c
t_palette	cycle_palettes(t_map *map);

// loops
void		keyhook(mlx_key_data_t keydata, void *param);
void		scrollhook(double xdelta, double ydelta, void *param);
void		user_inputs(void *param);
void		fdf_scale_and_project(void *param);
void		fdf_draw(void *param);

// fdf_projects
void		fdf_project(void *param, const int y, const int x);
void		fdf_project_optimized(void *param, const int y, const int x);

// utils_fdf.c
void		fdf_redraw(t_fdf *fdf);
void		fdf_scale(void *param, const int y, const int x);
void		fdf_center_offset(t_fdf *fdf);
void		fdf_reset_scale_and_offset(t_fdf *fdf);

// user_inputs_presets.c
void		input_presets_1(t_fdf *fdf);
void		input_presets_2(t_fdf *fdf);
void		input_hotkeys(t_fdf *fdf);

// utils_calc.c
double		deg_to_rad(double angle_deg);
double		rad_to_deg(double angle_rad);
double		ft_abs(double val);
short		ft_sign(double val);

// utils_init.c
void		map_init_preread(t_map *map, char *argv_1);
void		map_init_postread(t_map *map);
int			fdf_init(t_fdf *fdf, t_map *map);
void		fdf_line_init(t_line *line, t_map *map,
				const t_point *p0, const t_point *p1);
void		map_colour(void *param, const int y, const int x);
uint32_t	map_earth_colour(const t_map *map, const t_point *point);
uint32_t	line_colour(const t_line *line);

// utils_map.c
int			map_malloc_y(t_map *map);
int			map_malloc_x(t_map *map, const int y);
void		map_find_z_min_max(void *param, const int y, const int x);
void		map_free(t_map *map);
int			map_is_globe(const char *map_name);

// utils_misc.c

// fdf_draw_line.c
void		fdf_draw_down_and_to_the_right(void *param, const int y, const int x);
void		fdf_draw_line(const t_fdf *fdf, const t_point *p0, const t_point *p1);
void		fdf_draw_point(const t_fdf *fdf, const t_line *line);
int			fdf_check_point(const t_fdf *fdf, int x_pixel, int y_pixel);

// utils_draw.c
int			over_the_horizon(const t_fdf *fdf, t_line *line);
void		draw_background(const mlx_image_t *image, const uint32_t colour);

#endif