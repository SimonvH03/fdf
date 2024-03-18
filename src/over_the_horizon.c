/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over_the_horizon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/18 16:44:07 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// not using square roots because expensive
static int
	horizon_pythagoras(
		const t_fdf *fdf,
		const t_line *line,
		const t_point *point)
{
	double	a;
	double	b;

	if (line->i == 0 && line->j == 0
		&& (point->x * point->x) + (point->y * point->y)
		< (fdf->radius * fdf->radius))
		return (EXIT_FAILURE);
	if (line->swapped == false)
	{
		a = point->x + (line->i * line->s_ctl);
		b = point->y + (line->j * line->s_pas);
	}
	else
	{
		a = point->y + (line->i * line->s_ctl);
		b = point->x + (line->j * line->s_pas);
	}
	if ((a * a) + (b * b) < (fdf->radius * fdf->radius))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// swap points because I already implemented line drawing in any direction...
//		so why bother making two implementations for when p0 or p1 is OTH
static void
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

static int
	straight_horizon(
		const t_fdf *fdf,
		t_line *line)
{
	if (line->d_pas == 0)
	{
		while (line->i != line->d_ctl
			&& horizon_pythagoras(fdf, line, line->p0))
				line->i++;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int
	accurate_horizon(
		const t_fdf *fdf,
		t_line *line)
{
	int		p0_check;
	int		p1_check;

	p0_check = horizon_pythagoras(fdf, line, line->p0);
	p1_check = horizon_pythagoras(fdf, line, line->p1);
	if (p0_check == p1_check)
		return (p0_check);
	if (p1_check)
		line_swap_points(line);
	straight_horizon(fdf, line);
	while (line->i != line->d_ctl && line->j != line->d_pas
		&& horizon_pythagoras(fdf, line, line->p0))
	{
		if (line->err >= 0)
		{
			line->j += 1;
			line->err -= line->d_ctl;
		}
		line->i += 1;
		line->err += line->d_pas;
	}
	return (EXIT_SUCCESS);
}

// from draw_line.c / draw_line()
// we use pythagoras' theorum to see if x,y falls within the horizon
// Cases:
// if both points are over the horizon: skip
// if both points are outside the horizon: draw
// if only one point is over the horizon:
//		modify line to only draw from or until horizon
// 'darksquare' is used to increase performance by not calculating...
//		anything for lines with both points within predetermined region
// < 0.00001 instead of 0 because doubles also never round up
int
	over_the_horizon(
		const t_fdf *fdf,
		t_line *line)
{
	if (fdf->horizon == false || fdf->ballin == false)
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
