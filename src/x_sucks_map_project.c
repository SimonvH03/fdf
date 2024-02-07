/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:24:41 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/06 23:30:56 by simon            ###   ########.fr       */
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

static void	matrix_3x3_mltp(double ***res, double **a, double **b)
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
			*res[i][j] = 0;
			while (n <= j)
			{
				*res[i][j] += a[i][n] * b[n][j];
				n++;
			}
			j++;
		}
		i++;
	}
}

static double	**create_matrix(t_perspective *p)
{
	double			**res_matrix;
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

	res_matrix = (double **)malloc(3 * sizeof(double *));
	matrix_3x3_mltp(&res_matrix, matrix_alpha, matrix_beta);
	matrix_3x3_mltp(&res_matrix, res_matrix, matrix_gamma);
}

void	map_project(t_map *map, t_perspective *perspective)
{
	double	**rotation_matrix;
	int		y;
	int		x;

	//create rotation_matrix
	rotation_matrix = create_matrix(perspective);
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
