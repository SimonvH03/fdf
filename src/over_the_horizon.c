/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over_the_horizon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/15 18:04:51 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double
	distance_pythagoras(
		const double delta_a,
		const double delta_b)
{
	return (sqrt((delta_a * delta_a) + (delta_b * delta_b)));
}

// cheapest version of horizon check
// returns if point is outside of radius
int
	horizon_pythagoras(
		const t_fdf *fdf,
		const t_point *point)
{
	if ((point->x * point->x) + (point->y * point->y)
		< (fdf->radius * fdf->radius))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void
	line_swap_points(
		t_line *line)
{
	t_point	*temp;

	temp = (t_point *)line->p0;
	line->p0 = line->p1;
	line->p1 = temp;
	line->s_ctl *= -1;
	line->s_pas *= -1;
}

// if the line crosses the horizon (p0 ^ p1) we substitute it's
// inlying point with the crossing point.
// this is calculated by taking the distance from the point to radius
// then this ratio is used to traverse the line and find the subtitute point
int
	accurate_horizon(
		const t_fdf *fdf,
		t_line *line)
{
	int		p0_check;
	int		p1_check;

	p0_check = horizon_pythagoras(fdf, line->p0);
	p1_check = horizon_pythagoras(fdf, line->p1);
	if (p0_check && p1_check)
		return (EXIT_FAILURE);
	if (!p0_check && !p1_check)
		return (EXIT_SUCCESS);
	if (p1_check)
		line_swap_points(line);
	while (distance_pythagoras(line->p0->x + (line->i * line->s_ctl),
		line->p0->y + (line->j * line->s_pas)) < fdf->radius
		&& line->i < line->d_ctl && line->j < line->d_pas)
		{
			while (line->err >= 0)
			{
				line->j += 1;
				line->err -= line->d_ctl;
			}
			line->i += 1;
			line->err += line->d_pas;
		}
	return (EXIT_SUCCESS);
}

// then we use pythagoras' theorum to see if x,y falls within the horizon
// cases:
// if both points are over the horizon; return (1)
// if both points are outside the horizon; return (0)
// if only one point is over the horizon;
//;malloc a new point (with colour) exactly on the horizon and return (0)
int
	over_the_horizon(
		const t_fdf *fdf,
		t_line *line)
{
	if (fdf->ballin == false)
		return (EXIT_SUCCESS);
	if ((line->p0->z < -0.00001 && line->p1->z < -0.00001))
	{
		if (ft_abs(line->p0->x) < fdf->darksquare
			&& ft_abs(line->p0->y) < fdf->darksquare
			&& ft_abs(line->p1->x) < fdf->darksquare
			&& ft_abs(line->p1->y) < fdf->darksquare)
			return (EXIT_FAILURE);
		if (accurate_horizon(fdf, line) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
