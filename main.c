/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/02 15:42:07 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include <stdio.h>

#define WIDTH 1024
#define HEIGHT 1024

static int	err_return(char *error_msg)
{
	printf("%s", error_msg);
	return (-1);
}

static void	ft_hook(void *param)
{
	const mlx_t		*mlx = param;
	static	int32_t	previous_width;
	static	int32_t	previous_height;

	if (mlx_is_key_down((mlx_t *)mlx, MLX_KEY_ESCAPE))
	{
		printf("%s", "ESC pressed:\n\e[31mclosing window\n");
		mlx_close_window((mlx_t *)mlx);
	}
	if (mlx->width != previous_width || mlx->height != previous_height)
	{
		printf("\e[33mresize:\e[0m W: %d H: %d\n", mlx->width, mlx->height);
		previous_width = mlx->width;
		previous_height = mlx->height;
	}
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!mlx)
	{
		return (err_return("Error\n\e[31mmlx_init fail\n"));
	}
	image = mlx_new_image(mlx, 512, 512);
	if (!image)
	{
		mlx_close_window(mlx);
		return (err_return("Error\n\e[31mmlx_new_image fail\n"));
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		return (err_return("Error\n\e[31mmlx_image_to_window fail\n"));
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
