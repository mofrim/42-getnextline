/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:39 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/02 18:06:14 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Search for char c in string s. Return pointer to Position of c in s. */
char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *) s;
	while (*p)
	{
		if ((unsigned char)*p == (unsigned char)c)
			return (p);
		p++;
	}
	if ((unsigned char)c == '\0')
		return (p);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	char	*p;
	ssize_t	i;

	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	p = mem;
	i = -1;
	while (++i < size)
		p[i] = 0;
	return (mem);
}

void free_pointer(char **p)
{
	free(*p);
	*p = NULL;
}

char	*ft_strdup(const char *s)
{
	char	*c;
	int		i;

	c = (char *)malloc(ft_strlen(s) * sizeof (char) + 1);
	if (!c || !s)
		return (NULL);
	i = -1;
	while (s[++i])
		c[i] = s[i];
	c[i] = '\0';
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joi;
	char	*bak;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	joi = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof (char) + 1);
	bak = joi;
	if (!joi)
		return (NULL);
	while (*s1)
		*joi++ = *s1++;
	while (*s2)
		*joi++ = *s2++;
	*joi = '\0';
	return (bak);
}
size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p)
		p++;
	return (p - s);
}

