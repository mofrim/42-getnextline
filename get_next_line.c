/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/03 19:05:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **master_buf);

char	*get_next_line(int fd)
{
	static char		*master_buf[ULIMIT_N];
	char			*buf;
	char			*temp;
	
	ssize_t	read_return;

	// TODO: good idea?
	read_return = BUFFER_SIZE;
	buf = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (fd < 0 || !buf || BUFFER_SIZE <= 0)
		return (NULL);
	master_buf[fd] = ft_strdup("");
	while (!ft_strchr(master_buf[fd], '\n') && read_return == BUFFER_SIZE)
	{
		read_return = read(fd, buf, BUFFER_SIZE);
		temp = master_buf[fd];
		master_buf[fd] = ft_strjoin(master_buf[fd], buf);
		free_pointer(&temp);
	}
	if (read_return == -1)
		return (NULL);
	if (ft_strchr(master_buf[fd], '\n'))
		return(extract_line(&master_buf[fd]));
	else
		return(master_buf[fd]);
}

static char	*extract_line(char **master_buf)
{
	char	*newline_pos;
	char	*line;
	int		linelen;

	newline_pos = ft_strchr(*master_buf, '\n');
	linelen = 0;
	while ((*master_buf)[linelen] != '\n')
		linelen++;
	line = (char *) malloc((linelen + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (linelen >= 0)
	{
		line[linelen] = (*master_buf)[linelen];
		linelen--;
	}
	return (line);
}
