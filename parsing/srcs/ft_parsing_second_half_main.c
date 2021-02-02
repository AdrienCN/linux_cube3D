/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_main.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/02/02 11:25:02 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"
#define MAP_CHAR "012 WSNE"

int		ft_check_fullmap_format(char **map, int max_col, int max_row);
int		ft_make_oneline_map(int fd, t_cube *map_info);
int		ft_make_map(t_cube *map);
void	ft_copy_line_to_map(char *line, char **map, int max_col);
int		ft_wall_close_hze_check(char **map, int max_col, int max_row);
int		ft_wall_closed_vert_check(char **map, int max_row);
int		ft_zero_in_void_check(char **map);

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

int		ft_make_map(t_cube *map)
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

void	ft_copy_line_to_map(char *line, char **map, int max_col)
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

int		ft_emptyline_vert_check(char **map)
{
	int row;
	int col;
	int bol;

	col = 0;
	while (map[0][col] != '\0')
	{
		bol = 0;
		row = 0;
		while (map[row] != NULL)
		{
			if (map[row][col] != ' ')
				bol = 1;
			row++;
		}
		if (bol == 0)
			return (1);
		col++;
	}
	return (0);
}

int		ft_wall_closed_hze_check(char **map, int max_col)
{
	int i;
	int j;
	int k;

	i = 0;
	while (map[i] != NULL)
	{
		k = max_col - 1;
		j = 0;
		while (map[i][j] != '\0' && map[i][j] == ' ')
			j++;
		if (map[i][j] == '\0' || map[i][j] != '1')
			return (-1);
		while (k >= 0 && map[i][k] == ' ')
			k--;
		if (k < 0 || map[i][k] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int		ft_wall_closed_vert_check(char **map, int max_row)
{
	int i;
	int j;
	int k;

	i = 0;
	while (map[0][i] != '\0')
	{
		k = max_row - 1;
		j = 0;
		while (map[j] != NULL && map[j][i] == ' ')
			j++;
		if (map[j] == NULL || map[j][i] != '1')
			return (1);
		while (k >= 0 && map[k][i] == ' ')
			k--;
		if (k < 0 || map[k][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int		ft_zero_in_void_check(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
					return (1);
				if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_check_fullmap_format(char **map, int max_col, int max_row)
{
	(void)max_row;
	if (ft_emptyline_vert_check(map))
		return (-1);
	if (ft_wall_closed_hze_check(map, max_col) 
			|| ft_wall_closed_vert_check(map, max_row))
		return (-1);
	if (ft_zero_in_void_check(map))
	{
		printf("\t***ZERO_IN_VOID***\n");
		return (-1);
	}
	return (1);
}
