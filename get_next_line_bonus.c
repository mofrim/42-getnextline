/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/05 06:46:37 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char **master_buf, char *tmp);

int		read_data_from_file(int fd, char **master_buf, ssize_t *bytes_read);

void	update_masterbuf(int cnt, int linelen, char **master_buf, char *tmp);

char	*gnl_returnator(int bytes_read, char **master_buf, char *tmp);

/* The heart of this project. With only ONE function more i could have made the
 * code much more readable and shorter: free_ptr. But still this reads and
 * returns lines from filedes fd. */
char	*get_next_line(int fd)
{
	static char	*master_buf[ULIMIT_N];
	ssize_t		bytes_read;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	if (!master_buf[fd])
		master_buf[fd] = ft_strdup("");
	if (!master_buf[fd])
		return (NULL);
	while (!ft_strchr(master_buf[fd], '\n') && bytes_read == BUFFER_SIZE)
	{
		if (!read_data_from_file(fd, &master_buf[fd], &bytes_read))
		{
			free(master_buf[fd]);
			master_buf[fd] = NULL;
			return (NULL);
		}
	}
	tmp = NULL;
	return (gnl_returnator(bytes_read, &master_buf[fd], tmp));
}

/* Responsible for reading from file fd. Returns 0 if anything (malloc) goes
 * wrong down here. 1 otherwise.*/
int	read_data_from_file(int fd, char **master_buf, ssize_t *bytes_read)
{
	char	*buf;
	char	*temp;
	ssize_t	i;

	buf = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (0);
	*bytes_read = read(fd, buf, BUFFER_SIZE);
	if (*bytes_read > 0)
	{
		temp = *master_buf;
		*master_buf = ft_strjoin(*master_buf, buf);
		if (!(*master_buf))
		{
			free(buf);
			free(temp);
			return (0);
		}
		i = -1;
		while (++i <= BUFFER_SIZE)
			buf[i] = 0;
		free(temp);
	}
	free(buf);
	return (1);
}

/* The GNL-Returnator! Extracted function from main gnl to handle return value
 * of gnl. */
char	*gnl_returnator(int bytes_read, char **master_buf, char *tmp)
{
	if (bytes_read == -1 || (!bytes_read && !**master_buf))
	{
		free(*master_buf);
		*master_buf = NULL;
		return (NULL);
	}
	if (ft_strchr(*master_buf, '\n'))
	{
		tmp = extract_line(master_buf, tmp);
		if (!tmp)
		{
			free(*master_buf);
			*master_buf = NULL;
			return (NULL);
		}
		return (tmp);
	}
	else
	{
		tmp = ft_strdup(*master_buf);
		free(*master_buf);
		*master_buf = NULL;
		return (tmp);
	}
}

/* Extracts line from read data. Then calls update_masterbuf() to deal with the
 * remaining data. Returns the first line found or NULL if malloc fails. */
char	*extract_line(char **master_buf, char *tmp)
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
	cnt++;
	while (--cnt >= 0)
		line[cnt] = (*master_buf)[cnt];
	while ((*master_buf)[linelen + 1 + cnt])
		cnt++;
	if (!cnt)
	{
		free(*master_buf);
		*master_buf = NULL;
		return (line);
	}
	update_masterbuf(cnt, linelen, master_buf, tmp);
	return (line);
}

/* Removes the extracted line from master_buf, frees the old master_buf and
 * sets the master_buf pointer to mem containing the remaining data. No returns
 * but manages possible leaks by freeing stuff in case of failing allocs. */
void	update_masterbuf(int cnt, int linelen, char **master_buf, char *tmp)
{
	int		cntbak;
	char	*tmp_buf;

	cntbak = cnt + 1;
	tmp_buf = ft_calloc(cnt + 1, sizeof(char));
	if (!tmp_buf)
	{
		free(*master_buf);
		*master_buf = NULL;
		return ;
	}
	while (--cnt >= 0)
		tmp_buf[cnt] = (*master_buf)[linelen + 1 + cnt];
	tmp = *master_buf;
	*master_buf = (char *) ft_calloc(cntbak, sizeof(char));
	if (!(*master_buf))
	{
		free(tmp_buf);
		free(tmp);
		return ;
	}
	while (--cntbak >= 0)
		(*master_buf)[cntbak] = tmp_buf[cntbak];
	free(tmp);
	free(tmp_buf);
}
