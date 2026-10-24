/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2026/10/24 14:43:34 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Phase 2: keyhook
// 			scrollhook
// 			user_inputs
// Phase 3: project
// Phase 4: draw
static void
	loop_hooks(
		t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &keyhook, fdf);
	mlx_scroll_hook(fdf->mlx, &scrollhook, fdf);
	mlx_loop_hook(fdf->mlx, &user_inputs, fdf);
	mlx_loop_hook(fdf->mlx, &project, fdf);
	mlx_loop_hook(fdf->mlx, &draw, fdf);
}

int
	usage(
		char *program)
{
	ft_printf("usage: %s <map>\n", program);
	return (RETURN_FAILURE);
}

// Phase 1: map_init
// 			fdf_init
// 			menu_draw
int
	main(
		int argc,
		char **argv)
{
	t_map			map;
	t_fdf			fdf;

	if (argc != 2)
		return (usage(argv[0]));
	if (map_init(&map, argv[1]) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (fdf_init(&fdf, &map) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	menu_draw(&fdf);
	loop_hooks(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	map_free(&map);
	return (RETURN_SUCCESS);
}
