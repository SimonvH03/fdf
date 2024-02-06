/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:24:41 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/06 19:22:13 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_rotation_matrix	*matrix_3x3_multiplication(t_rotation_matrix *a,
					t_rotation_matrix *b)
{
	t_rotation_matrix	result_matrix;

	result_matrix.a.a = a->a.a * b->a.a + a->a.b * b->b.a + a->a.c * b->c.a;

	result_matrix = (t_rotation_matrix){
		{a->a.a*b->a.a+a->a.b*b->b.a+a->a.c*b->c.a,a->a.a*b->a.b+a->a.b*b->b.b+a->a.c*b->c.b,a->a.a*b->a.c+a->a.b*b->b.c+a->a.c*b->c.c},
		{a->b.a*b->a.a+a->b.b*b->b.a+a->b.c*b->c.a,a->b.a*b->a.b+a->b.b*b->b.b+a->b.c*b->c.b,a->b.a*b->a.c+a->b.b*b->b.c+a->b.c*b->c.c},
		{a->c.a*b->a.a+a->c.b*b->b.a+a->c.c*b->c.a,a->c.a*b->a.b+a->c.b*b->b.b+a->c.c*b->c.b,a->c.a*b->a.c+a->c.b*b->b.c+a->c.c*b->c.c},
	};
}

t_rotation_matrix	*create_rotation_matrix(t_perspective *p)
{
	t_rotation_matrix	matrix_alpha;
	t_rotation_matrix	matrix_beta;
	t_rotation_matrix	matrix_gamma;

	matrix_alpha = (t_rotation_matrix){
		{cos(p->alpha), -sin(p->alpha), 0},
		{sin(p->alpha), cos(p->alpha), 0},
		{0, 0, 1},
	};
	matrix_beta = (t_rotation_matrix){
		{cos(p->beta), 0, sin(p->beta)},
		{0, 1, 0},
		{-sin(p->beta), 0, cos(p->beta)}
	};
	matrix_gamma = (t_rotation_matrix){
		{1, 0, 0},
		{0, cos(p->gamma), -sin(p->gamma)},
		{0, sin(p->gamma), cos(p->gamma)}
	};
	return (matrix_3x3_multiplication(&matrix_alpha,
			matrix_3x3_multiplication(&matrix_beta,	&matrix_gamma)));
}

void	project_point_pretty(t_point *point, t_rotation_matrix *rotation_matrix)
{
	
	//matrix multiplication
}

void	project_point_compact(t_point *point, t_rotation_matrix *rotation_matrix)
{
	//matrix multiplication
}

void	project_map(t_map *map, t_perspective *perspective)
{
	t_rotation_matrix	*rotation_matrix;
	int					y;
	int					x;

	//create rotation_matrix
	rotation_matrix = create_rotation_matrix(perspective);
	//parse map
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			//put point and matrix into project_point function
			project_point_pretty(&map->content[y][x], rotation_matrix);
			x++;
		}
		y++;
	}
}
