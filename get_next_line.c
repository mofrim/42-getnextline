/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/02 11:00:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static char	*buf;

char *get_next_line(int fd)
{
	ssize_t	read_return;

	buf = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	read_return = read(fd, buf, BUFFER_SIZE);
	if (read_return == -1)
		return (NULL);



	return (NULL);
}




