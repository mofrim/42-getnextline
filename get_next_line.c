/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/04 16:26:21 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **master_buf);

void	read_data_from_file(int fd, char **master_buf, ssize_t *read_return, \
		char **temp);

void	update_masterbuf(int cnt, int linelen, char **master_buf);

char	*get_next_line(int fd)
{
	static char	*master_buf[ULIMIT_N];
	char		*temp;
	ssize_t		read_return;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_return = BUFFER_SIZE;
	if (!master_buf[fd])
		master_buf[fd] = ft_strdup("");
	while (!ft_strchr(master_buf[fd], '\n') && read_return == BUFFER_SIZE)
		read_data_from_file(fd, &master_buf[fd], &read_return, &temp);
	if (read_return == -1 || (!read_return && !*master_buf[fd]))
	{
		free_ptr(&master_buf[fd]);
		return (NULL);
	}
	if (ft_strchr(master_buf[fd], '\n'))
		return (extract_line(&master_buf[fd]));
	else
	{
		temp = ft_strdup(master_buf[fd]);
		free_ptr(&master_buf[fd]);
		return (temp);
	}
}

void	read_data_from_file(int fd, char **master_buf, ssize_t *read_return, \
		char **temp)
{
	char	*buf;
	ssize_t	i;

	buf = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
	{
		*master_buf = NULL;
		return ;
	}
	*read_return = read(fd, buf, BUFFER_SIZE);
	if (*read_return > 0)
	{
		*temp = *master_buf;
		*master_buf = ft_strjoin(*master_buf, buf);
		if (!(*master_buf))
			return ;
		i = -1;
		while (++i <= BUFFER_SIZE)
			buf[i] = 0;
		free_ptr(temp);
	}
	free_ptr(&buf);
}

char	*extract_line(char **master_buf)
{
	char	*line;
	int		linelen;
	int		cnt;

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
	while ((*master_buf)[linelen + 1 + cnt])
		cnt++;
	if (!cnt)
	{
		free_ptr(master_buf);
		return (line);
	}
	update_masterbuf(cnt, linelen, master_buf);
	return (line);
}

void	update_masterbuf(int cnt, int linelen, char **master_buf)
{
	int		cntbak;
	char	*tmp_buf;
	char	*master_tmp;

	cntbak = cnt + 1;
	tmp_buf = ft_calloc(cnt + 1, sizeof(char));
	if (!tmp_buf)
	{
		*master_buf = NULL;
		return ;
	}
	while (--cnt >= 0)
		tmp_buf[cnt] = (*master_buf)[linelen + 1 + cnt];
	master_tmp = *master_buf;
	*master_buf = (char *) ft_calloc(cntbak, sizeof(char));
	if (!(*master_buf))
		return ;
	while (--cntbak >= 0)
		(*master_buf)[cntbak] = tmp_buf[cntbak];
	free_ptr(&master_tmp);
	free_ptr(&tmp_buf);
}

void	free_ptr(char **p)
{
	free(*p);
	*p = NULL;
}
