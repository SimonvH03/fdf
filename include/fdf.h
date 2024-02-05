/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/05 21:14:54 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <MLX42/MLX42.h>
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
// for printf, exclude later
# include <stdio.h>

# define WIDTH 1024
# define HEIGHT 1024

//Colours
# define C_LINES 0xFFFFFFFF
# define C_BACKGROUND 0x00000000

// projection
typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	uint32_t	colour;
}	t_point;

typedef struct s_rotation_matrix
{
	int			a;
	int			b;
	int			c;
}	t_rotation_matrix;

// single use
typedef struct s_map
{
	t_point		**content;
	int			fd;
	char		*name;
	int			x_max;
	int			y_max;
}	t_map;

typedef struct s_fdf
{
	mlx_image_t	*image;
	t_map		*map;
	mlx_t		*mlx;
}	t_fdf;


//structs_init
t_map				map_init(char *map_name);
t_fdf				fdf_init(t_map *map);

//structs_free
void				map_free(t_map *map);
void				fdf_free(t_fdf *fdf);

t_map				*read_map(t_map *map);

//test_utils
void				check_map_result(t_map *map);

#endif