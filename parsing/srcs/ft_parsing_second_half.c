/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/01/30 10:22:37 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"
#define MAP_CHAR "012 WSNE"

static char	*ft_cube_strjoin(char const *s1, char const *s2, char const *sep);

int		ft_make_map(int fd, t_cube *map_info);

int		ft_second_parsing(int fd, t_cube *map_info)
{
	map_info->map = NULL;
	if (ft_make_map(fd, map_info) == -1)
		return (-1);
	/*
	if (ft_map_shape_check(map) == -1)
		return (-1);
		*/
	return (1);
}

int		ft_make_map(int fd, t_cube *map_info)
{
	int gnl;
	char *line;
	char *map;
	char *tmp;

	line = NULL;
	tmp = NULL;
	map = NULL;
	gnl = get_next_line(fd, &line);
	while (gnl > 0)
	{
		// Leaks GNL:
		// -Free line a chaque appel
		// -Free storage DANS GNL au dernier appel de GNL ....?
/*	
		if (!ft_line_char_check(line, MAP_CHAR))
		{
			free(tmp);
			free(map);
			free(line);
			return (-1);
		}
		*/
		tmp = map;
		map = ft_cube_strjoin(map, line, "@@@");
		free(tmp);
		free(line);
		map = NULL;
		line = NULL;
		gnl = get_next_line(fd, &line);

	}
	free(line);
	map_info->map = NULL;
	return (0);
}

static char	*ft_cube_strjoin(char const *s1, char const *s2, char const *sep)
{
	char	*str;
	size_t	l1;
	size_t	l2;
	size_t	sep_len;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	sep_len = ft_strlen(sep);
	str = malloc(sizeof(char) * (l1 + sep_len + l2 + 1));
	if (str == NULL)
		return (NULL);
	ft_memmove(str, s1, l1);
	ft_memmove(str + l1, sep, sep_len);
	ft_memmove(str + l1 + sep_len, s2, l2);
	str[l1 + sep_len + l2] = '\0';
	return (str);
}
