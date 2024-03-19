/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spellbook[1].c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:11:55 by simon             #+#    #+#             */
/*   Updated: 2023/12/18 19:29:20 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_cprint(char c)
{
	return (ft_putchar(c));
}

int	ft_idprint(int id)
{
	return (ft_putnbr(id));
}

int	ft_uprint(unsigned int u)
{
	return (ft_putnbr(u));
}

int	ft_xprint(int x)
{
	return (ft_putnbr_base(x, "0123456789abcdef"));
}

int	ft_bigxprint(int x)
{
	return (ft_putnbr_base(x, "0123456789ABCDEF"));
}
