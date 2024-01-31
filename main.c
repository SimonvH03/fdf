/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/01/31 22:01:44 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include <stdio.h>

#define WIDTH 512
#define HEIGHT 512

static void	ft_hook(void *param)
{
	const mlx_t	*mlx = param;

	if (mlx_is_key_down((mlx_t *)mlx, MLX_KEY_ESCAPE))
	{
		printf("%s", "ESC pressed:\t\e[31mclosing window\n");
		mlx_close_window((mlx_t *)mlx);
	}
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	if (!mlx)
	{
		printf("%s", "Error\n\t\e[31mmlx_init fail");
		return (-1);
	}
	image = mlx_new_image(mlx, 512, 512);
	if (!image)
	{
		printf("%s", "Error\n\t\e[31mmlx_new_image fail");
		mlx_close_window(mlx);
		return (-1);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		printf("%s", "Error\n\t\e[31mmlx_image_to_window fail");
		mlx_close_window(mlx);
		return (-1);
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
