/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:11:09 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/01/03 17:49:13 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

char	*ft_strjoin_gnl(char **newline, const char *buffer);
char	*ft_strdup_gnl(const char *buffer);
char	*ft_read_gnl(char **newline, char *buffer, int fd);
void	ft_remainder_gnl(char *buffer);

void	*ft_free_gnl(char **p);
int		ft_strlen_gnl(const char *src);
int		ft_strchr_gnl(const char *str, char c);
void	ft_memclear_gnl(char *buffer, size_t n);

#endif