/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/01/31 10:47:21 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"
#define MAP_CHAR "012 WSNE"

static char	*ft_cube_strjoin(char const *s1, char const *s2, char const *sep);
static int	ft_line_char_check(char *line, char *base, t_cube *map_info);
int		ft_isbase(char c, char *base);

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
	char *line;
	char *map;
	char *tmp;

	line = NULL;
	tmp = NULL;
	map = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		// Leaks GNL:
		// -Free storage DANS GNL au dernier appel de GNL ....?
		if (ft_line_char_check(line, MAP_CHAR, map_info) == -1)
		{
			printf("\t****_____LINE_FORMAT___ERROR___****\n");
			free(map);
			free(line);
			return (-1);
		}
		tmp = map;
		map = ft_cube_strjoin(map, "@", line);
		free(tmp);
		if (map == NULL)
			return (-1);
		free(line);
		tmp = NULL;
		line = NULL;

	}
	printf("Full_map_in_one_line:\n%s\n", map);
	map_info->map = ft_split(map, '@');
	free(map);
	free(line);
	return (0);
}

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

static int	ft_line_char_check(char *line, char *base, t_cube *map_info)
{
	unsigned int i;

	i = 0;
	printf("line :[%s]\n", line);
	while (line[i] != '\0')
	{
		if (!ft_isbase(line[i], base))
			return (-1);
		if (ft_isbase(line[i], "NESW"))
		{
			if (map_info->player == '0')
				map_info->player = line[i];
			else
				return (-1);
		}
		i++;
	}
	return (1);
}

static char	*ft_cube_strjoin(char const *s1, char const *sep, char const *s2)
{
	char *tmp;
	char *new_str;
	
	if (s1 == NULL)	
		new_str = ft_strjoin("", sep);
	else
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
