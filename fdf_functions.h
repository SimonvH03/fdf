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

#ifndef FDF_FUNCTIONS_H
# define FDF_FUNCTIONS_H
# include "MLX42/MLX42.h"

# include "fdf_defines.h"
# include "fdf_structs.h"

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
void		map_cycle_palettes(t_map *map);

void		map_toggle_squish(t_fdf *fdf);

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
mapi_func	map_squish;

//// PHASE 4: drawing the fdf based on the projection data
mlx_hook	draw;
void		draw_line(const t_fdf *fdf, const t_point *p0, const t_point *p1);
void		draw_line_init(t_line *line, const t_point *p0, const t_point *p1);
int			over_the_horizon(const t_fdf *fdf, t_line *line);

//// UTILS
// map
int			map_free(t_map *map);
int			map_free_err(t_map *map);
void		map_set_z_boundaries(t_map *map);
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