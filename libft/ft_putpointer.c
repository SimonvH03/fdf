/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:15:27 by simon             #+#    #+#             */
/*   Updated: 2023/12/20 18:26:57 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_libft.h"

int	ft_putpointer(unsigned long p)
{
	int	len;

	len = 0;
	len += ft_putstr("0x");
	len += ft_putnbr_base(p, "0123456789abcdef");
	return (len);
}
