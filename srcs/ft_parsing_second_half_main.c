/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_main.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/03/13 12:37:37 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static char **ft_malloc_the_map(int max_row, int max_col);
static char	**ft_create_mapgrid(char *line, int max_row, int max_col);

int		ft_second_parsing(int fd, t_cube *cube)
{
	int error;

	if ((error = ft_make_oneline_map(fd, cube)))
		return (error);
	if (close(fd) < 0)
		return (ft_parsing_error_msg(1, -3));
	printf("m_line = %s\n", cube->m_line);
	cube->map = ft_create_mapgrid(cube->m_line, cube->max_row, cube->max_col);
	if (cube->map == NULL)
		return (-3);
	if ((error = ft_check_fullmap_format(cube->map, cube)))
		return (error);
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
