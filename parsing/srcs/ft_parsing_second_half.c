/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/01/29 17:14:42 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"
#define MAP_CHAR "012 WSNE"

int		ft_second_parsing(int fd, t_cube *map_info)
{
	char **map;
	if (ft_make_map(fd, map_info) == -1)
		return (-1);
	if (ft_map_shape_check(map) == -1)
		return (-1);
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
	gnl = get_next_line(fd, line);
	while (gnl > 0)
	{
		if (!ft_line_char_check(line, MAP_CHAR))
		{
			free(tmp);
			free(map);
			return (-1);
		}
		tmp = line;


