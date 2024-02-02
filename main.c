/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/02 17:06:29 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static int	err_return(char *error_msg)
{
	printf("%s", error_msg);
	return (-1);
}

static void	ft_background(void *param)
{
	mlx_image_t	*image;
	uint32_t	x;
	uint32_t	y;

	image = param;
	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, x, y, 0xFF000099);
			x++;
		}
		y++;
	}
}

static void	ft_hook(void *param)
{
	mlx_t			*mlx;
	static int32_t	previous_width;
	static int32_t	previous_height;

	mlx = param;
	if (mlx_is_key_down((mlx_t *)mlx, MLX_KEY_ESCAPE))
	{
		printf("%s", "\e[33mESC pressed\n\e[31m:closing window\n");
		mlx_close_window((mlx_t *)mlx);
	}
	if (mlx->width != previous_width || mlx->height != previous_height)
	{
		printf("\e[33mresized\n\e[0m:W: %d H: %d\n", mlx->width, mlx->height);
		previous_width = mlx->width;
		previous_height = mlx->height;
	}
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "fdf", false);
	if (!mlx)
	{
		return (err_return("Error\n\e[31m:mlx_init fail\n"));
	}
	image = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!image)
	{
		mlx_close_window(mlx);
		return (err_return("Error\n\e[31m:mlx_new_image fail\n"));
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		return (err_return("Error\n\e[31m:mlx_image_to_window fail\n"));
	}
	mlx_loop_hook(mlx, create_wireframe, image);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
