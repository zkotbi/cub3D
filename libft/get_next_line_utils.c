/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:21:49 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/25 08:30:36 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	strl(const char *s1)
{
	int	i;

	i = 0;
	while (s1 && s1[i] != 0)
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;
	int		j;

	j = strl(s1);
	i = 0;
	res = malloc(sizeof(const char) * (j + 1));
	malloc_null_check(res);
	while (i < j)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strchr(const char	*s, int c)
{
	char	i;

	i = (char )c;
	while (*s != 0)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i != 0)
	{
		return (NULL);
	}
	return ((char *)s);
}

char	*ft_strjoin(char	*s1, char *s2, int r)
{
	int		l;
	char	*rt;
	int		i;

	i = 0;
	l = strl(s1) + r;
	rt = malloc(l + 1);
	if (rt == NULL)
		return (ft_memdel(&s1));
	while (s1 && s1[i] != 0)
	{
		rt[i] = s1[i];
		i++;
	}
	while (*s2 != 0)
	{
		rt[i] = *s2;
		s2++;
		i++;
	}
	rt[i] = 0;
	ft_memdel(&s1);
	return (rt);
}

char	*ft_memdel(char	**ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
	return (NULL);
}
