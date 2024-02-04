/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/04 18:23:23 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>

#define WIDTH 1024
#define HEIGHT 1024
#define DELIMITER ' '

typedef struct s_map
{
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

t_map	*read_map(t_map *map);