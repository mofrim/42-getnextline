/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/04 11:59:59 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **master_buf);

char	*get_next_line(int fd)
{
	static char		*master_buf[ULIMIT_N];
	char			*buf;
	char			*temp;
	
	ssize_t	read_return;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_return = BUFFER_SIZE;
	buf = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	if(!master_buf[fd])
	{
		master_buf[fd] = ft_strdup("");
	}
	while (!ft_strchr(master_buf[fd], '\n') && read_return == BUFFER_SIZE)
	{
		read_return = read(fd, buf, BUFFER_SIZE);
		if (read_return > 0)
		{
			temp = master_buf[fd];
			master_buf[fd] = ft_strjoin(master_buf[fd], buf);
			ft_bzero(buf, BUFFER_SIZE);
			free_ptr(&temp);
		}
	}
	free(buf);
	if (read_return == -1)
	{
		free_ptr(&master_buf[fd]);
		return (NULL);

	}
	if (!read_return && !*master_buf[fd])
	{
		free_ptr(&master_buf[fd]);
		return(NULL);
	}
	if (ft_strchr(master_buf[fd], '\n'))
		return(extract_line(&master_buf[fd]));
	else
	{
		temp = ft_strdup(master_buf[fd]);
		free_ptr(&master_buf[fd]);
		return(temp);
	}
}

char	*extract_line(char **master_buf)
{
	char	*tmp_buf;
	char	*line;
	char	*supertmp;
	int		linelen;
	int		cnt;
	int		cntbak;

	cnt = 0;
	while ((*master_buf)[cnt] != '\n')
		cnt++;
	linelen = cnt;
	line = (char *) ft_calloc(linelen + 2, sizeof(char));
	if (!line)
		return (NULL);
	while (cnt >= 0)
	{
		line[cnt] = (*master_buf)[cnt];
		cnt--;
	}
	while((*master_buf)[linelen + 1 + cnt])
		cnt++;
	cntbak = cnt + 1;
	if (!cnt)
	{
		free_ptr(master_buf);
		return (line);
	}
	tmp_buf = ft_calloc(cnt + 1, sizeof(char));
	while (--cnt >= 0)
		tmp_buf[cnt] = (*master_buf)[linelen + 1 + cnt];
	supertmp = *master_buf;
	*master_buf = (char *) ft_calloc(cntbak, sizeof(char));
	while (--cntbak >= 0)
		(*master_buf)[cntbak] = tmp_buf[cntbak];
	free_ptr(&supertmp);
	free(tmp_buf);
	tmp_buf = NULL;

	return (line);
}
