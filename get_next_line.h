/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:39:24 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/02 18:11:02 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 100

/* `ulimit -n` on my system. Number of open files per process. */
# define ULIMIT_N 1024

/* For ssize_t and NULL*/
# include <stddef.h>

/* For write & read */
# include <unistd.h>

/* For malloc & free */
# include <stdlib.h>

char	*get_next_line(int fd);
void	free_pointer(char **p);

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
