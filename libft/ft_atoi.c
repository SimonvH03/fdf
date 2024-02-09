/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:55:23 by svan-hoo          #+#    #+#             */
/*   Updated: 2023/10/30 22:05:49 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *c)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*c == ' ' || (*c >= 9 && *c <= 13))
		c++;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			sign = -sign;
		c++;
	}
	while (*c >= '0' && *c <= '9')
		num = (num * 10) + (*c++ - '0');
	return (sign * num);
}