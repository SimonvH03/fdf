/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:01 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/16 01:27:05 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// turn degree angle into radian
double
	deg_to_rad(
		double angle_deg)
{
	return (angle_deg * PI / 180);
}

// return absolute value
double
	ft_abs(
		double value)
{
	if (value < 0)
		return (-value);
	return (value);
}

// return polarity of value
short
	ft_sign(
		double value)
{
	if (value < 0)
		return (-1);
	if (value > 0)
		return (1);
	return (0);
}
