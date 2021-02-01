/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/02/01 15:40:53 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"
#define MAP_CHAR "012 WSNE"

static char	*ft_cube_strjoin(char const *s1, char const *s2, char const *sep);
static int	ft_line_char_check(char *line, char *base, t_cube *map_info);
int		ft_isbase(char c, char *base);
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

void	ft_set_row_col(char *line, t_cube *map)
{
	int max_len;
	
	max_len = ft_strlen(line);
	if (max_len > map->max_col)
		map->max_col = max_len;
	map->max_row += 1;
}
static int		ft_empty_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			printf("empty = false\n");
			return (0);
		}
		i++;
	}
	printf("empty = TRUE\n");
	return (1);
}

int	ft_make_oneline_map_two(char *gnl_line, t_cube *map)
{
	char *tmp;

	if (ft_line_char_check(gnl_line, MAP_CHAR, map) == -1)
	{
		printf("\t****_____LINE_FORMAT___ERROR___****\n");
		return (-1);
	}
	ft_set_row_col(gnl_line, map);
	tmp = map->m_line;
	map->m_line = ft_cube_strjoin(map->m_line, "@", gnl_line);
	free(tmp);
	if (map == NULL)
		return (-1);
	return (1);
}


int		ft_make_oneline_map(int fd, t_cube *map_info)
{
	char *line;

	line = map_info->gnl_line;
	while (get_next_line(fd, &line) > 0)
	{
		// Leaks GNL:
		// -Free storage DANS GNL au dernier appel de GNL ....?
		if (map_info->map_start == TRUE && ft_empty_line(line) == FALSE)
			map_info->map_start = FALSE;
		if (map_info->map_start == FALSE && map_info->map_end == FALSE)
		{
			if (ft_empty_line(line) == TRUE)
				map_info->map_end = TRUE;
			else if (ft_make_oneline_map_two(line, map_info) == -1)
					return (-1);
		}
		else if (map_info->map_end == TRUE && ft_empty_line(line) == FALSE)
			return (-1);
		free(line);
	}
	if (map_info->max_col == 0 || map_info->max_row == 0)
		return (-1);
	free(map_info->gnl_line);
	map_info->gnl_line = NULL;
	return (1);
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
		return (ft_strdup(s2));
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
