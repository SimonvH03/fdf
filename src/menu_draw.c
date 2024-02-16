/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:50 by simon             #+#    #+#             */
/*   Updated: 2024/02/16 15:09:17 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	menu_print(t_fdf *fdf)
{
	const int	margin = 48;
	const int	linespace = 32;

	mlx_put_string(fdf->mlx, "menu", margin, margin);
}

void	menu_draw(t_fdf *fdf)
{
	draw_background(fdf->menu_image, C_MENU);
	mlx_image_to_window(fdf->mlx, fdf->menu_image, 0, 0);
	menu_print(fdf);
}
