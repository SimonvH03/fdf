/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/05 18:18:01 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	loop_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &keyhook, fdf);
	mlx_scroll_hook(fdf->mlx, &scrollhook, fdf);
	mlx_loop_hook(fdf->mlx, &user_inputs, fdf);
	mlx_loop_hook(fdf->mlx, &map_scale, fdf);
	mlx_loop_hook(fdf->mlx, &map_project, fdf);
	mlx_loop_hook(fdf->mlx, &fdf_draw, fdf);
}

int	main(int argc, char **argv)
{
	t_map			map;
	t_perspective	perspective;
	t_fdf			fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	map = (t_map)
	{NULL, NULL, NULL, argv[1], 0, 0, 0, 0, 0, 1};
	map_read(&map);
	perspective = (t_perspective)
	{ISO_ALPHA, ISO_BETA, ISO_GAMMA};
	if (fdf_init(&fdf, &map, &perspective) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	menu_draw(&fdf);
	loop_hooks(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	map_free(&map);
	return (EXIT_SUCCESS);
}
