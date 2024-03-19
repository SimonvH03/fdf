/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:11:18 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/19 17:30:06 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/get_next_line.h"

void	*ft_free_gnl(char **pp)
{
	free(*pp);
	*pp = NULL;
	return (NULL);
}

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int	ft_strchr_gnl(const char *str, char c)
{
	int	i;

	i = 0;
	if (str)
		while (str[i] || str[i] == c)
			if (str[i++] == c)
				return (i);
	return (0);
}

void	ft_memclear_gnl(char *src, size_t n)
{
	while (n--)
		src[n] = 0;
}
