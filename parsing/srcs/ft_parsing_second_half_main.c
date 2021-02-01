/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_main.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/02/01 16:51:50 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"
#define MAP_CHAR "012 WSNE"

int		ft_check_fullmap_format(t_cube *map);
int		ft_make_oneline_map(int fd, t_cube *map_info);
int		ft_make_map(char *line, t_cube *map_info);
void	ft_copy_line_to_map(char *line, char **map, int max_col);

int		ft_second_parsing(int fd, t_cube *map_info)
{
	if (ft_make_oneline_map(fd, map_info) == -1)
		return (-1);	
	if (ft_make_map(map_info->m_line, map_info) == -1)
		return (-1);
	ft_copy_line_to_map(line, map->map, map->max_col);
	if (ft_check_fullmap_format(map_info) == -1)
		return (-1);
	return (1);
}

int		ft_make_map(char *line, t_cube *map)
{
	int i;

	map->map = malloc(sizeof(*map->map) * (map->max_row + 1));
	if (map->map == NULL)
		return (-1);
	map->map[map->max_row] = NULL;
	i = 0;
	while (i < map->max_row)
	{
		map->map[i] = malloc(sizeof(**map->map) * (map->max_col + 1));
		if (map->map[i] == NULL)
			return (-1);
		map->map[i][map->max_col] = '\0';
		i++;
	}
	return (1);
}

void	ft_copy_line_to_map(char *line, char **map, int max_col)
{
	int i;
	int row;
	int col;

	i = 0;
	row = 0;
	while (line[i] != '\0')
	{
		col = 0;
		while (line[i] != '@' && line[i] != '\0')
		{
			map[row][col] = line[i];
			col++;
			i++;
		}
		while (col < max_col)
		{
			map[row][col] = ' ';
			col++;
		}
		row++;
		i++;
	}
}

int		ft_check_fullmap_format(t_cube *map)
{
	if (ft_emptyline_vert_check(map))
		return (-1);
	if (ft_wall_closed_hze_check(map) || ft_wall_closed_vert_check(map))
		return (-1);
	if (ft_zero_in_void_check(map))
		return (-1);
	return (1);
}
	
/*
 
int		ft_empty_line_vert_check(char **map)
{
	int row;
	int col;
	int only_space;

	col = 0;
	while (map[0][col] != '\0')
	{
		row = 0;
		only_space = TRUE;
		while (map[row][col] != '\0)
			return (0);
	}
}

int		ft_wall_closed_hze_check(char **map);
int		ft_wall_closed_vert_check(char **map);
int		ft_zero_in_void_check(char **map);




*/
