/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/05 00:32:59 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

#define WIDTH 1024
#define HEIGHT 1024

typedef struct s_map
{
	char		*name;
	int			fd;
	int			x;
	int			y;
	int			**content;
}	t_map;

typedef struct s_wireframe
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_map		*map;
}	t_wireframe;

//structs_init
void	map_init(t_map *map);
void	wireframe_init(t_wireframe *wireframe);

//structs_free
void	map_free(t_map *map);
void	wireframe_free(t_wireframe *wireframe);

t_map	*read_map(t_map *map);