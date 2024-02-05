/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/05 19:04:54 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <MLX42/MLX42.h>
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>

# define WIDTH 1024
# define HEIGHT 1024

//Colours
# define C_LINES 0xFFFFFFFF
# define C_BACKGROUND 0x00000000

// single use
typedef struct s_map
{
	char		*name;
	int			fd;
	int			x_max;
	int			y_max;
	int			**content;
}	t_map;

typedef struct s_wireframe
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_map		*map;
}	t_wireframe;

// projection
typedef struct s_vector
{
	int			x;
	int			y;
	int			z;
}	t_vector;

typedef struct s_point
{
	t_vector	*vector;
	uint32_t	colour;
}	t_point;

typedef struct s_rotation_matrix
{
	int			alpha;
	int			beta;
	int			gamma;
}	t_rotation_matrix;


//structs_init
t_map				*map_init(char *map_name);
t_wireframe			*wireframe_init(t_map *map);
t_vector			*vector_init(void);
t_point				*point_init(t_vector *vector);
t_rotation_matrix	*rotation_matrix_init(void);

//structs_free
void				map_free(t_map *map);
void				wireframe_free(t_wireframe *wireframe);

t_map				*read_map(t_map *map);

//test_utils
void				check_map_result(t_map *map);

#endif