/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/01/30 10:58:00 by calao            ###   ########.fr       */
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
	map = malloc(sizeof(char) * 1);
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
		map = ft_cube_strjoin(map, "@", line);
		free(tmp);
		if (map == NULL)
			return (-1);
		//free(line);
		//tmp = NULL;
		//line = NULL;
		gnl = get_next_line(fd, &line);

	}
	free(line);
	printf("Full_map_in_one_line:\n%s\n", map);
	map_info->map = ft_split(map, '@');
	return (0);
}

static char	*ft_cube_strjoin(char const *s1, char const *sep, char const *s2)
{
	char *tmp;
	char *new_str;

	new_str = ft_strjoin(s1, sep);
	if (new_str == NULL)
		return (NULL);
	tmp = new_str;
	new_str = ft_strjoin(new_str, s2);
	free(tmp);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}
