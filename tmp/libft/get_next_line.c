/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:43:32 by adconsta          #+#    #+#             */
/*   Updated: 2021/01/28 19:17:55 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_make_line(char *storage)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (storage == NULL)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
	{
		free(storage);
		return (NULL);
	}
	j = 0;
	while (storage[j] && j < i)
	{
		line[j] = storage[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_update_storage(char *storage)
{
	int		i;
	char	*new_str;

	i = 0;
	if (storage == NULL)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\0')
	{
		free(storage);
		return (NULL);
	}
	i++;
	new_str = ft_gnlstrdup(storage + i);
	free(storage);
	return (new_str);
}

int		read_file(char **storage, char **line, char *buf, int fd)
{
	int res;

	res = 1;
	while (((look_for_newline(storage[fd])) == 0)
			&& ((res = read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[res] = '\0';
		if ((storage[fd] = ft_gnlstrjoin(storage[fd], buf)) == NULL)
			return (-1);
	}
	if (res == -1)
		return (res);
	if ((*line = ft_make_line(storage[fd])) == NULL)
		return (-1);
	if ((storage[fd] = ft_update_storage(storage[fd])) == NULL
			&& res != 0)
		return (-1);
	res = (res == 0 ? 0 : 1);
	return (res);
}

int		get_next_line(int fd, char **line)
{
	static char *storage[256];
	char		*buf;
	int			res;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (storage[fd] == NULL)
		if ((storage[fd] = ft_gnlstrdup("")) == NULL)
			return (-1);
	if ((buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1))) == NULL)
		return (-1);
	res = read_file(storage, line, buf, fd);
	free(buf);
	return (res);
}
