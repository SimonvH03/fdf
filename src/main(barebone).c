/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/07 23:43:21 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_fdf			fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, true);
	if (fdf.mlx == NULL)
		return (EXIT_FAILURE);
	fdf.image = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (fdf.image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(fdf.mlx, fdf.image, 0, 0) == -1)
		return (EXIT_FAILURE);
	mlx_loop_hook(fdf.mlx, &ft_background, fdf.image);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
