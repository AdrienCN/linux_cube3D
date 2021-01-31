/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:40:47 by calao             #+#    #+#             */
/*   Updated: 2021/01/31 15:57:41 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"
#define MAP_CHAR "012 WSNE"

static char	*ft_cube_strjoin(char const *s1, char const *s2, char const *sep);
static int	ft_line_char_check(char *line, char *base, t_cube *map_info);
int		ft_isbase(char c, char *base);
int		ft_map_shape_check(char **map);
char	*ft_make_oneline_map(int fd, t_cube *map_info);
char	**ft_make_map(char *line, t_cube *map_info);

int		ft_second_parsing(int fd, t_cube *map_info)
{
	char *line_map;
	map_info->map = NULL;
	line_map = ft_make_oneline_map(fd, map_info);
	if (line_map == NULL)
		return (-1);

	printf("Full_map_in_one_line:\n%s\n", line_map);
	
	if (ft_make_map(line_map, map_info) == -1)
	{
		free(map_info->map);
		free(line_map);
		return (-1);
	}
	free(line_map);
	return (1);
}
char	*ft_make_oneline_map(char *line, t_cube *map_info)
{
	char *line;
	char *map;
	char *tmp;

	line = NULL;
	tmp = NULL;
	map = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		// Leaks GNL:
		// -Free storage DANS GNL au dernier appel de GNL ....?
		if (ft_line_char_check(line, MAP_CHAR, map_info) == -1)
		{
			printf("\t****_____LINE_FORMAT___ERROR___****\n");
			free(map);
			free(line);
			return (NULL);
		}
		tmp = map;
		map = ft_cube_strjoin(map, "@", line);
		free(tmp);
		if (map == NULL)
			return (NULL);
		free(line);
		tmp = NULL;
		line = NULL;
	}
	free(line);
	return (map);
}

int		ft_map_maxlinenbr(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '@')
			count++;
		i++;
	}
	return (count);
}

int		ft_map_maxlinelen(char *line)
{
	int i;
	int cur_len;
	int max_len;

	max_len = 0;
	cur_len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '@')
		{
			if (cur_len > max_len)
				max_len = cur_len;
			cur_len = 0;
		}
		i++;
		cur_len++;
	}
	return (max_len);
}

void	ft_fill_square(char **map, int row, int col)
{
	int i;
	int j;

	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			map[i][j] == ' ';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	j = 0;
	while (j < col)
	{
		map[i][j] = '\0';
		j++;
	}
	map[i][j] = '\0';
}

void	ft_copy_map_to_square(char *line, t_cube *map)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '@')
		{
			k = 0;
			j++;
		}
		else
		{
			map[j][k] = line[i];
			k++;
		}
			i++;
	}
}
	
int		ft_make_map(char *line, t_cube *map)
{
	int i;
	
	map->m_max_row = ft_map_maxlinenbr(line);
	map->m_max_col = ft_map_maxlinelen(line);
	map->map = malloc(sizeof(*char) * (map->m_max_row + 1));
	if (map->map == NULL)
		return (-1);
	i = 0;
	while (i < line_nbr)
	{
		map->map[i] = malloc(sizeof(char) * (map->m_max_col + 1));
		if (map->map[i] == NULL)
		{
			ft_free_double_map->map(map->map);
			return (-1);
		}
		i++;
	}
	ft_fill_square(map->map, map->m_max_row, map->m_max_col);
	ft_copy_map_to_square(line, map); 
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
		new_str = ft_strjoin("", sep);
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
