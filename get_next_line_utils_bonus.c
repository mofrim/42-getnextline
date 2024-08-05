/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:39 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/05 06:47:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

/* Alloc and fill with zeros. */
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

/* Allocate enough space & return duplicated string str. */
char	*ft_strdup(const char *str)
{
	char	*dupl;
	int		i;

	dupl = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!dupl || !str)
		return (NULL);
	i = -1;
	while (str[++i])
		dupl[i] = str[i];
	dupl[i] = '\0';
	return (dupl);
}

/* Allocated enough space for the joining of string s1 and s2 and return the
 * joined string. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jstr;
	char	*jstr_bak;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	jstr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	jstr_bak = jstr;
	if (!jstr)
		return (NULL);
	while (*s1)
		*jstr++ = *s1++;
	while (*s2)
		*jstr++ = *s2++;
	*jstr = '\0';
	return (jstr_bak);
}

/* Well, strlen. */
size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p)
		p++;
	return (p - s);
}
