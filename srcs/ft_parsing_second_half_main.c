/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_main.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/02/16 17:52:07 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static char **ft_make_map(int max_row, int max_col);
static char	**ft_copy_line_to_map(char *line, int max_row, int max_col);

int		ft_second_parsing(int fd, t_cube *cube)
{
	if (ft_make_oneline_map(fd, cube) == -1)
		return (-1);
	if ((cube->map = ft_copy_line_to_map(cube->m_line, cube->max_row,
											cube->max_col)) == NULL)
		return (-1);
	if (ft_check_fullmap_format(cube->map, cube->max_col, cube->max_row) == -1)
		return (-1);
	return (1);
}

static char **ft_copy_line_to_map(char *line, int max_row, int max_col)
{
	int i;
	int row;
	int col;
	char **map;
	
	map = ft_make_map(max_row, max_col);
	if (map == NULL)
		return (NULL);
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
	return (map);
}

static char	**ft_make_map(int max_row, int max_col)
{
	int i;
	char	**tab;

	tab = malloc(sizeof(*tab) * (max_row + 1));
	if (tab == NULL)
		return (NULL);
	tab[max_row] = NULL;
	i = 0;
	while (i < max_row)
	{
		tab[i] = malloc(sizeof(**tab) * (max_col + 1));
		if (tab[i] == NULL)
			return (NULL);
		tab[i][max_col] = '\0';
		i++;
	}
	return (tab);
}


