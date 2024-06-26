/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/28 15:26:42 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define PI 3.14159265358979

// mlx window
# define WINDOW_TITLE "fdf"
# define WIDTH 2000
# define HEIGHT 1600
# define MENU_WIDTH 400

// fdf defaults
# define DEFAULT_SCALE 0.7
# define ROTATION_SPEED 0.01

// perspective defaults
# define ISO_GAMMA -0.7853981633974483
# define ISO_BETA 0
# define ISO_ALPHA -0.6154729074232804

// colours
# define C_WHITE			0xFFFFFFFF
# define C_GRAY				0x808080FF
# define C_BLACK			0x000000FF
# define C_BACKGROUND		0x868078FF
# define C_MENU				0xFF000040

// palette RGB
# define P_RGB_NR			0
# define C_RGB_BACK			C_BLACK
# define C_RGB_LOW			0x0000FFFF
# define C_RGB_MID			0x00FF00FF
# define C_RGB_HIGH			0xFF0000FF

// palette HACKERMAN
# define P_HACKERMAN_NR		1
# define C_HACKERMAN_BACK	0x080810FF
# define C_HACKERMAN_LOW	0x003300FF
# define C_HACKERMAN_MID	0x006600FF
# define C_HACKERMAN_HIGH	0x00FF00FF

// palette Metal
# define P_METAL_NR			2
# define C_METAL_BACK		0x202030FF
# define C_METAL_LOW		C_BLACK
# define C_METAL_MID		C_GRAY
# define C_METAL_HIGH		C_WHITE

// palette Pastel
// # define P_PASTEL_NR		3
// # define C_PASTEL_BACK		0x20002088
// # define C_PASTEL_LOW		0x85D65CFF
// # define C_PASTEL_MID		0xFBBBC8FF
// # define C_PASTEL_HIGH		0xFFE840FF

// palette Rust
# define P_RUST_NR			4
# define C_RUST_BACK		0x080810FF
# define C_RUST_LOW			0x660000FF
# define C_RUST_MID			0xFF6644FF
# define C_RUST_HIGH		0xAAAAAAFF

// palette Earth
# define P_EARTH_NR			5
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
	bool			swapped;
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
typedef struct s_map
{
	t_point			**original;
	t_point			**project;
	t_point			**polar;
	t_palette		palette;
	int				fd;
	char			*name;
	bool			isearth;
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
	int				sign;
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
	bool			horizon;
	double			darksquare;
	double			radius;
}	t_fdf;

//// PHASE 0: function types
// function type used to modify points on a (t_point **) type map
typedef	void	(mapi_func)(void *param, const int y, const int x);
// function type undefined by MLX42
typedef void	(mlx_hook)(void *param);
// because 'mlx_scrollfunc' would force all declarations 4 to the right, L norm
typedef void	(mlx_key)(struct mlx_key_data, void *);
typedef void	(mlx_scroll)(double, double, void *);

//// PHASE 1: initialising windows, maps and settings based on map
// map
int			map_init(t_map *map, char *map_name);
int			map_read(t_map *map);
mapi_func	map_colour;
// fdf (mlx window)
int			fdf_init(t_fdf *fdf, t_map *map);
// draw the menu because it's static anyway
void		menu_draw(t_fdf *fdf);

//// PHASE 2: interpreting user input to set up point modification
mlx_hook	user_inputs;
mlx_key		keyhook;
mlx_scroll	scrollhook;

// presets for spherical or flat projection
void		input_presets_flat(t_fdf *fdf);
void		input_presets_balls(t_fdf *fdf);

// change the projection's colour palette
t_palette	map_cycle_palettes(t_map *map);

//// PHASE 3: modifying the projection data based on interpreted user input
mlx_hook	project;
// Mother of Death, responsible for 9 victims, with some of with her children
// loops over map and applies function with each point's [y][x] coordinates
void		map_iteration(t_map *map, mapi_func *function, void *param);
// MoD's children, the map iteration functions
mapi_func	fdf_rotate;
mapi_func	fdf_rotate_optimized;
mapi_func	fdf_scale;
mapi_func	map_fill_polar;
mapi_func	map_set_polar;
mapi_func	map_set_original;

//// PHASE 4: drawing the fdf based on the projection data
mlx_hook	draw;
void		draw_line(const t_fdf *fdf, const t_point *p0, const t_point *p1);
void		draw_line_init(t_line *line, const t_point *p0, const t_point *p1);
int			over_the_horizon(const t_fdf *fdf, t_line *line);

//// UTILS
// map
int			map_free(t_map *map);
int			map_free_err(t_map *map);
// map_read
int			map_calloc_y(t_map *map);
int			map_calloc_x(t_map *map, const int y);
// fdf
void		fdf_center_offset(t_fdf *fdf);
// draw
void		draw_background(const mlx_image_t *image, const uint32_t colour);
int			draw_check_point(const t_fdf *fdf, int x_pixel, int y_pixel);
uint32_t	gradient(double ratio, uint32_t end, uint32_t start);
// calc
double		deg_to_rad(double angle_deg);
double		ft_abs_double(double val);
short		ft_sign_double(double val);

#endif