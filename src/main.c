/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/09 21:35:47 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void
	loop_hooks(
		t_fdf	*fdf)
{
	mlx_key_hook(fdf->mlx, &keyhook, fdf);
	mlx_scroll_hook(fdf->mlx, &scrollhook, fdf);
	mlx_loop_hook(fdf->mlx, &user_inputs, fdf);
	mlx_loop_hook(fdf->mlx, &fdf_scale_and_project, fdf);
	mlx_loop_hook(fdf->mlx, &fdf_draw, fdf);
}

int
	main(
		int argc,
		char	**argv)
{
	t_map			map;
	t_fdf			fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	map = (t_map)
	{NULL, NULL, NULL, (t_coordinates){0, 0}, (t_palette){0,0,0}, argv[1], 0, 0, 0, 0, 0, 0};
	if (map_read(&map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fdf_init(&fdf, &map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map_init(&map);
	menu_draw(&fdf);
	loop_hooks(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	map_free(&map);
	return (EXIT_SUCCESS);
}
