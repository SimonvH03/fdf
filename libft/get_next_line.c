/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:11:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/04 11:44:42 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_gnl(const char *buffer)
{
	int		i;
	char	*temptr;

	i = ft_strchr_gnl(buffer, '\n');
	if (i == 0)
		i = ft_strlen_gnl(buffer);
	temptr = (char *)malloc((i + 1) * sizeof(char));
	if (temptr == NULL)
		return (NULL);
	temptr[i] = '\0';
	while (i--)
		temptr[i] = buffer[i];
	return (temptr);
}

char	*ft_strjoin_gnl(char **nextline, const char *buffer)
{
	char		*temptr;
	const int	n_len = ft_strlen_gnl(*nextline);
	const int	b_len = ft_strlen_gnl(buffer);
	const int	b_nl = ft_strchr_gnl(buffer, '\n');
	int			i;

	if (b_nl == 0)
		i = n_len + b_len;
	else
		i = n_len + b_nl;
	temptr = (char *)malloc((i + 1) * sizeof(char));
	if (temptr == NULL)
		return (ft_free_gnl(nextline));
	temptr[i] = '\0';
	while (i-- > n_len)
		temptr[i] = buffer[i - n_len];
	i += 1;
	while (i--)
	{
		temptr[i] = (*nextline)[i];
	}
	ft_free_gnl(nextline);
	return (temptr);
}

char	*ft_read_gnl(char **nextline, char *buffer, int fd)
{
	int		bytes_read;

	bytes_read = BUFFER_SIZE;
	while (bytes_read == BUFFER_SIZE && !ft_strchr_gnl(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free_gnl(nextline));
		buffer[bytes_read] = '\0';
		*nextline = ft_strjoin_gnl(nextline, buffer);
		if (*nextline == NULL)
			return (NULL);
	}
	return (*nextline);
}

void	ft_remainder_gnl(char *buffer)
{
	const char	*remainder = buffer + ft_strchr_gnl(buffer, '\n');
	int			i;

	i = 0;
	if (remainder > buffer)
	{
		while (remainder[i])
		{
			buffer[i] = remainder[i];
			i++;
		}
	}
	ft_memclear_gnl(buffer + i, BUFFER_SIZE - i);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*nextline;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	nextline = ft_strdup_gnl(buffer);
	if (nextline == NULL)
	{
		ft_memclear_gnl(buffer, BUFFER_SIZE + 1);
		return (NULL);
	}
	nextline = ft_read_gnl(&nextline, buffer, fd);
	if (nextline == NULL)
	{
		ft_memclear_gnl(buffer, BUFFER_SIZE + 1);
		return (NULL);
	}
	ft_remainder_gnl(buffer);
	if (nextline[0] == 0)
		return (ft_free_gnl(&nextline));
	return (nextline);
}

// int	main(void)
// {
// 	int			fd;
// 	int			line;
// 	char		*nextline;

// 	line = 0;
// 	fd = open("text.txt", O_RDONLY);
// 	while (line < 15)
// 	{
// 		nextline = get_next_line(fd);
// 		printf("\nline %d:\t%s", line, nextline);
// 		line++;
// 		if (nextline == NULL)
// 			break ;
// 		free(nextline);
// 	}
// 	close(fd);
// 	return (0);
// }