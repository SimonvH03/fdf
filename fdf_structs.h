/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:59:02 by svan-hoo      #+#    #+#                 */
/*   Updated: 2026/10/24 15:30:41 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCTS_H
# define FDF_STRUCTS_H

# include "fdf_defines.h"

typedef struct s_point
{
	uint32_t		colour;
	double			x;
	double			y;
	double			z;
}	t_point;

typedef struct s_line
{
	const t_point	*p0;
	const t_point	*p1;
	int				d_ctl;
	int				d_pas;
	int				s_ctl;
	int				s_pas;
	int				err;
	int				i;
	int				j;
	bool			swapped;
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

typedef struct s_step
{
	short			alpha;
	short			beta;
	short			gamma;
	int				sign;
	bool			reproject;
}	t_step;

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

typedef enum e_scroll_behaviour
{
	move = 0,
	rotate,
	squish,
	zoom,
	max
}	t_scroll;

typedef struct s_fdf
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*menu_image;
	t_map			*map;
	t_perspective	perspective;
	t_step			step;
	t_cosin			cosin;
	t_scale			scale;
	t_offset		center;
	t_offset		offset;
	t_scroll		scroll_behaviour;
	double			speed;
	double			alt_speed;
	double			squish_factor;
	double			darksquare;
	double			radius;
	bool			ballin;
	bool			horizon;
	bool			redraw;
	bool			spin_lock;
	bool			squished;
}	t_fdf;

#endif