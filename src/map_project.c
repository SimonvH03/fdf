/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:24:41 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/06 22:08:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	point_matrix_mltp(t_point *point, double **b_3x3)
{
	double			result_vector[3];
	const double	point_vector[3] = {point->x, point->y, point->z};
	int				i;
	int				n;

	i = 0;
	while (i < 3)
	{
		n = 0;
		result_vector[i] = 0;
		while (n < 3)
		{
			result_vector[i] += point_vector[i] * b_3x3[i][n];
			n++;
		}
		i++;
	}
	point->x = result_vector[0];
	point->y = result_vector[1];
	point->z = result_vector[2];
}

static void	matrix_3x3_mltp(double ***res_3x3, double **a_3x3, double **b_3x3)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			n = 0;
			*res_3x3[i][j] = 0;
			while (n <= j)
			{
				*res_3x3[i][j] += a_3x3[i][n] * b_3x3[n][j];
				n++;
			}
			j++;
		}
		i++;
	}
}

static void	create_matrix(double ***rm, t_perspective *p)
{
	const double	matrix_alpha[3][3] = {
	{cos(p->alpha), -sin(p->alpha), 0},
	{sin(p->alpha), cos(p->alpha), 0},
	{0, 0, 1}};
	const double	matrix_beta[3][3] = {
	{cos(p->beta), 0, sin(p->beta)},
	{0, 1, 0},
	{-sin(p->beta), 0, cos(p->beta)}};
	const double	matrix_gamma[3][3] = {
	{1, 0, 0},
	{0, cos(p->gamma), -sin(p->gamma)},
	{0, sin(p->gamma), cos(p->gamma)}};

	matrix_3x3_mltp(rm, (double **)matrix_alpha, (double **)matrix_beta);
	matrix_3x3_mltp(rm, *rm, (double **)matrix_gamma);
}

void	map_project(t_map *map, t_perspective *perspective)
{
	double	**rotation_matrix;
	int		y;
	int		x;

	//create rotation_matrix
	create_matrix(&rotation_matrix, perspective);
	//parse map
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			//put point and matrix into project_point function
			point_matrix_mltp(&map->content[y][x], rotation_matrix);
			x++;
		}
		y++;
	}
}
