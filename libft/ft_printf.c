/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:13:52 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/19 18:28:29 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_spellbook(va_list args, const char *form)
{
	int	bytes_printed;

	if (*form == '%')
		return (ft_cprint('%'));
	if (*form == 'c')
		return (ft_cprint(va_arg(args, int)));
	if (*form == 's')
		return (ft_sprint(va_arg(args, char *)));
	if (*form == 'i' || *form == 'd')
		return (ft_idprint(va_arg(args, int)));
	if (*form == 'u')
		return (ft_uprint(va_arg(args, unsigned int)));
	if (*form == 'x')
		return (ft_xprint(va_arg(args, int)));
	if (*form == 'X')
		return (ft_bigxprint(va_arg(args, unsigned int)));
	if (*form == 'p')
		return (ft_pprint(va_arg(args, void *)));
	bytes_printed = write(1, "%%", 1);
	bytes_printed += write(1, form, 1);
	return (bytes_printed);
}

int	ft_printf(const char *form, ...)
{
	va_list	args;
	int		bytes_printed;
	int		i;

	va_start(args, form);
	bytes_printed = 0;
	i = 0;
	while (form[i])
	{
		if (form[i] == '%')
			bytes_printed += ft_spellbook(args, (form + ++i));
		else
			bytes_printed += write(1, (form + i), 1);
		i++;
	}
	va_end(args);
	return (bytes_printed);
}
