/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:45:15 by simon             #+#    #+#             */
/*   Updated: 2024/03/19 17:30:06 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

int	ft_str_toupper(char *src)
{
	const int	slen = ft_strlen(src);
	int			i;

	i = 0;
	while (i < slen)
	{
		src[i] = ft_toupper(src[i]);
		i++;
	}
	return (i);
}
