/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/07 02:17:53 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// static int	err_return(mlx_t *mlx, char *error_msg)
// {
// 	if (mlx)
// 		mlx_close_window(mlx);
// 	printf("%s", error_msg);
// 	return (-1);
// }

// static void	clear_image(void *param)
// {
// 	mlx_image_t	*image;
// 	uint32_t	x;
// 	uint32_t	y;

// 	image = param;
// 	y = 0;
// 	while (y < image->height)
// 	{
// 		x = 0;
// 		while (x < image->width)
// 		{
// 			mlx_put_pixel((mlx_image_t *)image, x, y, C_BACKGROUND);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	ft_hook(void *param)
// {
// 	mlx_t			*mlx;
// 	static int32_t	previous_width;
// 	static int32_t	previous_height;

// 	mlx = param;
// 	if (mlx_is_key_down((mlx_t *)mlx, MLX_KEY_ESCAPE))
// 	{
// 		printf("%s", "\e[33mESC pressed\n\e[31m:closing window\n");
// 		mlx_close_window((mlx_t *)mlx);
// 	}
// 	if (mlx->width != previous_width || mlx->height != previous_height)
// 	{
// 		printf("\e[33mresized\n\e[0m:W: %d H: %d\n", mlx->width, mlx->height);
// 		previous_width = mlx->width;
// 		previous_height = mlx->height;
// 	}
// }

// void	loop_hooks(mlx_t *mlx, mlx_image_t *image, t_fdf *fdf)
// {
// 	mlx_loop_hook(mlx, ft_hook, mlx);
// 	mlx_loop_hook(mlx, ft_background, image);
// }

int main(int argc, char **argv)
{
	t_map map;
	t_perspective perspective;
	// mlx_t			mlx;
	// t_fdf			fdf;

	if (argc != 2)
		return (1);
	map = (t_map){NULL, 0, argv[1], 0, 0};
	map_fill_content(&map);
	printf("\nmap.x_max: %d\nmap.y_max: %d\n", map.x_max, map.y_max);
	check_map_result(&map, "read", 'z');
	perspective = (t_perspective){45, 0, atan(30)};
	map_project(&map, &perspective);
	check_map_result(&map, "projected", 'x');
	check_map_result(&map, "projected", 'y');
	check_map_result(&map, "projected", 'z');
	map_free(&map);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	mlx_t		*mlx;
// 	mlx_image_t	*image;
// 	t_fdf	*fdf;

// 	if (argc != 2)
// 		return (0);
// 	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
// 	if (!mlx)
// 		return (err_return(mlx, "Error\n\e[31m:mlx_init fail\n"));
// 	image = mlx_new_image(mlx, mlx->width, mlx->height);
// 	if (!image)
// 		return (err_return(mlx, "Error\n\e[31m:mlx_new_image fail\n"));
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 		return (err_return(mlx, "Error\n\e[31m:mlx_image_to_window fail\n"));
// 	init_fdf(argv[1]);
// 	loops_hooks(mlx, image, fdf);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (0);
// }
