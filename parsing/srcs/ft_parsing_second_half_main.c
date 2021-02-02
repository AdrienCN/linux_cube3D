/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_main.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/02/02 11:49:15 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"

static int		ft_make_map(t_cube *map);
static void	ft_copy_line_to_map(char *line, char **map, int max_col);

int		ft_second_parsing(int fd, t_cube *map_info)
{
	if (ft_make_oneline_map(fd, map_info) == -1)
		return (-1);
	printf("making map....\n");
	if (ft_make_map(map_info) == -1)
		return (-1);
	printf("copying line to map...\n");
	ft_copy_line_to_map(map_info->m_line, map_info->map, map_info->max_col);
	printf("checking edges & void ...\n");
	if (ft_check_fullmap_format(map_info->map, map_info->max_col, map_info->max_row) == -1)
		return (-1);
	return (1);
}

static int		ft_make_map(t_cube *map)
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
	printf("m_row = %d | m_col = %d\n", map->max_row, map->max_col);
	return (1);
}

static void	ft_copy_line_to_map(char *line, char **map, int max_col)
{
	int i;
	int row;
	int col;

	i = 0;
	row = 0;
	while (map[row] != NULL && line[i] != '\0')
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
		i++;
		row++;
	}
}
