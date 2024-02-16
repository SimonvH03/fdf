/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:50 by simon             #+#    #+#             */
/*   Updated: 2024/02/16 17:35:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	menu_print(t_fdf *fdf)
{
	const int	margin = 48;
	const int	line = 24;
	const int	tab = 24;
	int			y;

	y = margin - line;
	mlx_put_string(fdf->mlx, "Menu", margin, (y += line));
	mlx_put_string(fdf->mlx, "subtext", margin + tab, (y += line));
}

void	menu_draw(t_fdf *fdf)
{
	draw_background(fdf->menu_image, C_MENU);
	mlx_image_to_window(fdf->mlx, fdf->menu_image, 0, 0);
	menu_print(fdf);
}
