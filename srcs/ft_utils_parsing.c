/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:04:20 by calao             #+#    #+#             */
/*   Updated: 2021/03/14 01:14:11 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

int		ft_isbase(char c, char *base)
{
	unsigned int i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
			return (1);
		i++;
	}
	return (0);
}

int		ft_empty_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_file_ext_name(char *filename, char *ext_name)
{
	unsigned int i;

	i = 0;
	while (filename[i] != '\0')
	{
		if (filename[i] == '.')
		{
			if (filename[i + 1] != '.' && filename[i + 1] != '/')
				break ;
		}
		i++;
	}
	if (ft_strcmp(&filename[i], ext_name) == 0)
		return (0);
	printf("Error: not valid file. Use '%s' file\n", ext_name);
	return (1);
}

int		ft_is_file_readable(char *file_path)
{
	int		fd;
	int		ret;
	char	buf;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	ret = read(fd, &buf, 1);
	if (ret < 0)
		return (-2);
	close(fd);
	if (fd < 0)
		return (-3);
	return (0);
}
