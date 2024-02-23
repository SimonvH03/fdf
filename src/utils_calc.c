/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:01 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/23 19:20:42 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// turn degree angle into radial
double	rad(double angle_deg)
{
	const double	ratio = 180 / PI;

	return (angle_deg / ratio);
}

// return absolute value
double	ft_abs(double val)
{
	if (val < 0)
		return (-val);
	return (val);
}

// return polarity of value
short	ft_sign(double val)
{
	if (val < 0)
		return (-1);
	if (val > 0)
		return (1);
	return (0);
}
