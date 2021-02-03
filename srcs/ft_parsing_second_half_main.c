/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_main.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/02/03 12:20:05 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static int		ft_make_map(t_cube *cube);
static void	ft_copy_line_to_map(char *line, char **map, int max_col);

int		ft_second_parsing(int fd, t_cube *cube)
{
	if (ft_make_oneline_map(fd, cube) == -1)
		return (-1);
	if (ft_make_map(cube) == -1)
		return (-1);
	ft_copy_line_to_map(cube->m_line, cube->map, cube->max_col);
	if (ft_check_fullmap_format(cube->map, cube->max_col, cube->max_row) == -1)
		return (-1);
	return (1);
}

static int		ft_make_map(t_cube *cube)
{
	int i;

	cube->map = malloc(sizeof(*cube->map) * (cube->max_row + 1));
	if (cube->map == NULL)
		return (-1);
	cube->map[cube->max_row] = NULL;
	i = 0;
	while (i < cube->max_row)
	{
		cube->map[i] = malloc(sizeof(**cube->map) * (cube->max_col + 1));
		if (cube->map[i] == NULL)
			return (-1);
		cube->map[i][cube->max_col] = '\0';
		i++;
	}
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
