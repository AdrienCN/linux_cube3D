/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_main.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/02/01 16:08:05 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"
#define MAP_CHAR "012 WSNE"

int		ft_map_shape_check(char **map);
int		ft_make_oneline_map(int fd, t_cube *map_info);
int		ft_make_map(char *line, t_cube *map_info);

int		ft_second_parsing(int fd, t_cube *map_info)
{
	int bol;

	bol = 1;
	if (ft_make_oneline_map(fd, map_info) == -1)
		bol = 0;	

	printf("....Creating the map...\n");
	
	if (bol == 1 && ft_make_map(map_info->m_line, map_info) == -1)
		bol = 0;
	if (bol == 1)
		return (1);
	else
	{
		//free toute la structure 
		//free(map_info->map);
		return (-1);
	}
}

void	ft_copy_map_to_grid(char *line, char **map, int max_col)
{
	int i;
	int row;
	int col;

	i = 0;
	row = 0;
	printf("ft_strlen(line)= %ld\n", ft_strlen(line));
	while (line[i] != '\0')
	{
		col = 0;
		while (line[i] != '@' && line[i] != '\0')
		{
			//printf("map[%d][%d] = [%c] | line[%d] = %c\n", row, col, map[row][col], i, line[i]);
			map[row][col] = line[i];
			col++;
			i++;
		}
		// Options A : while (map[row][col] != '\0')
		while (col < max_col)
		{
			map[row][col] = 'x';
			col++;
		}
	//	printf("line %.2d:[%s]\t len = %ld\n", row, map[row], ft_strlen(map[row]));
		row++;
		i++;
	}
}
	
int		ft_make_map(char *line, t_cube *map)
{
	int i;
	char **tab;
	
	tab = malloc(sizeof(*tab) * (map->max_row + 1));
	if (tab == NULL)
		return (-1);
	printf("row = %d | col = %d\n", map->max_row, map->max_col);
	tab[map->max_row] = NULL;
	i = 0;
	while (i < map->max_row)
	{
		tab[i] = malloc(sizeof(**tab) * (map->max_col + 1));
		if (tab[i] == NULL)
		{
			//ft_free_double_tab(tab);
			return (-1);
		}
		tab[i][map->max_col] = '\0';
		i++;
	}
	printf("\n___i___ = %d\n\n", i);
	//printf("Jusqu'ici tout va bien\n");
	//printf("Le plus important ce n'est pas la chute mais l'atterissage\n");
	ft_copy_map_to_grid(line, tab, map->max_col);
	map->map = tab;
	return (0);
}
/*
 
int		ft_empty_line_hze_check(char **map);
{
	int row;
	int col;
	int only_space;

	row = 0;
	while (map[row] != '\0')
	{
		only_space = TRUE;
		col = 0;
		while (map[row][col] != '\0')
		{
			if (map[row][col] != ' ')
				only_space = FALSE;
			col++;
		}
		if (only_space == TRUE)
			return (1);
		row++;
	}
	return (0);
}

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

int		ft_empty_line_vert_check(char **map);
int		ft_wall_closed_hze_check(char **map);
int		ft_wall_closed_vert_check(char **map);
int		ft_zero_in_void_check(char **map);


int		ft_map_shape_check(char **map)
{
	if (ft_emptyline_hze_check(map) || ft_emptyline_vert_check(map))
		return (-1);
	if (ft_wall_closed_hze_check(map) || ft_wall_closed_vert_check(map))
		return (-1);
	if (ft_zero_in_void_check(map))
		return (-1);
	return (1);
}

*/
