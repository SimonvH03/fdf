/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:01 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/01 15:00:54 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// turn degree angle into radian
double	deg_to_rad(double angle_deg)
{
	return (angle_deg * PI / 180);
}

double	rad_to_deg(double angle_rad)
{
	return (angle_rad * 180 / PI);
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
