/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:45:15 by simon             #+#    #+#             */
/*   Updated: 2023/12/16 23:48:14 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcat(char *dest, const char *src)
{
	const int	dlen = ft_strlen(dest);
	const int	slen = ft_strlen(src);
	int			i;

	i = 0;
	while (i < slen)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	return (i);
}
