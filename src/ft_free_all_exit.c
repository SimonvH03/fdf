/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:21:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/04/18 21:38:57 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// in this function we free() everything we could have possibly malloc'd
void
	ft_free_all_exit(
		t_map *map
	)
{
	free();
	free();
	free();
	free();
	free();
	exit(EXIT_FAILURE);
}

t_point	**
	ft_calloc_fdf(
		t_map *map,
		size_t size
	)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (ptr == NULL)
		ft_free_all_exit(map);
	ft_bzero(ptr, size);
	return (ptr);
}
