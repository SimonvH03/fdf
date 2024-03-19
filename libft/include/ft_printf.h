/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:36:11 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/19 18:27:15 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int	ft_printf(const char *form, ...);
int	ft_spellbook(va_list args, const char *form);

int	ft_cprint(char c);
int	ft_sprint(char *str);
int	ft_idprint(int id);
int	ft_uprint(unsigned int u);
int	ft_xprint(int x);
int	ft_bigxprint(int x);
int	ft_pprint(void *p);

#endif