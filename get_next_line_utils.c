/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:39 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/04 10:34:40 by fmaurer          ###   ########.fr       */
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
	int		memsize;
	char	*p;
	ssize_t	i;

	memsize = nmemb * size;
	mem = malloc(memsize);
	if (!mem)
		return (NULL);
	p = mem;
	i = -1;
	while (++i < memsize)
		p[i] = 0;
	return (mem);
}

void free_ptr(char **p)
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
	char	*joined_str;
	char	*jstr_bak;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	joined_str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	jstr_bak = joined_str;
	if (!joined_str)
		return (NULL);
	while (*s1)
		*joined_str++ = *s1++;
	while (*s2)
		*joined_str++ = *s2++;
	*joined_str = '\0';
	return (jstr_bak);
}
size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p)
		p++;
	return (p - s);
}

