/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_main.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/03/12 18:54:16 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static char **ft_malloc_the_map(int max_row, int max_col);
static char	**ft_create_mapgrid(char *line, int max_row, int max_col);

int		ft_second_parsing(int fd, t_cube *cube)
{
	int error;

	if ((error = ft_make_oneline_map(fd, cube)))
	{
		// -1 Non allowed charactere in map_grid
		// -2 Map has more than one player.
		// -3 error in map_join from char * to char **. malloc has failed;
		// -4 Horizontal empty line in map_grid
		// -5 map must contains min 1 row and 1 col
		return (error);
	}
	cube->map = ft_create_mapgrid(cube->m_line, cube->max_row, cube->max_col);
	if (cube->map == NULL)
	{
		// Malloc has failed
		return (-3);
	}
	if ((error = ft_check_fullmap_format(cube->map, 
					cube->max_col, cube->max_row)))
	{
		// -6 Empty line found vertically
		// -7 Wall missing. Map must be surrounded by '1'
		// -8 void found in the map
		return (error);
	}
	return(0);
}

static char **ft_create_mapgrid(char *line, int max_row, int max_col)
{
	int i;
	int row;
	int col;
	char **map;
	
	map = ft_malloc_the_map(max_row, max_col);
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

static char	**ft_malloc_the_map(int max_row, int max_col)
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
