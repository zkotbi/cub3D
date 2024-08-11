/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:21:45 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/08 23:01:07 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char	*ft_read(char	*backup, int fd)
{
	int		r;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (ft_memdel(&backup));
	*buf = 0;
	while (ft_strchr(buf, '\n') == NULL)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
			return (ft_memdel(&buf),
				exit_strerror("cannot read from file\n", 1), NULL);
		else if (r == 0)
			break ;
		buf[r] = 0;
		backup = ft_strjoin(backup, buf, r);
		if (backup == NULL)
			return (ft_memdel(&buf),
				exit_strerror("malloc failure\n", 1), NULL);
	}
	ft_memdel(&buf);
	return (backup);
}

static char	*ft_line(char	*backup)
{
	int		i;
	int		j;
	char	*rtline;

	i = 0;
	j = 0;
	while (backup[i] != 0 && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		rtline = malloc(i + 2);
	else
		rtline = malloc(i + 1);
	if (rtline == NULL)
		return (exit_strerror("malloc failure\n", 1), NULL);
	while (backup[j] != '\n' && backup[j] != 0)
	{
		rtline[j] = backup[j];
		j++;
	}
	if (backup[j] == '\n')
		rtline[j++] = '\n';
	rtline[j] = 0;
	return (rtline);
}

static char	*ft_backup(char	*backup, int *check)
{
	int		i;
	char	*rt_back;

	i = 0;
	if (backup[i] == 0)
		return (*check = 0, ft_memdel(&backup));
	while (backup[i] != 0 && backup[i] != '\n')
		i++;
	if (backup[i] == 0)
		return (*check = 0, ft_memdel(&backup));
	if (backup[i + 1] == 0 || backup + i + 1 == NULL)
		return (*check = 0, ft_memdel(&backup));
	rt_back = ft_strdup(backup + i + 1);
	if (rt_back == NULL)
		return (*check = -1, ft_memdel(&backup));
	ft_memdel(&backup);
	return (*check = 0, rt_back);
}

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*line;
	int			check;

	line = NULL;
	check = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647
		|| read(fd, &check, 0) < 0)
		return (ft_memdel(&backup),
			exit_strerror("cannot read from file\n", 1), NULL);
	backup = ft_read(backup, fd);
	if (backup == NULL)
		return (NULL);
	line = ft_line(backup);
	if (line == NULL)
		return (ft_memdel(&backup));
	backup = ft_backup(backup, &check);
	if (backup == NULL && check == -1)
		return (ft_memdel(&backup), exit_strerror("malloc failure\n", 1), NULL);
	return (line);
}
