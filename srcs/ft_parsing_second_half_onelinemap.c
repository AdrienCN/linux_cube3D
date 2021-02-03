/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_onelinemap.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:54:38 by calao             #+#    #+#             */
/*   Updated: 2021/02/03 12:20:21 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static void		ft_set_row_col(char *line, t_cube *map);
static int	ft_make_oneline_map_two(char *gnl_line, t_cube *map);
static char	*ft_cube_strjoin(char const *s1, char const *sep, char const *s2);
static int	ft_line_char_check(char *line, char *base, t_cube *map_info);

int		ft_make_oneline_map(int fd, t_cube *map_info)
{
	char *line;

	while (get_next_line(fd, &map_info->gnl_line) > 0)
	{
		line = map_info->gnl_line;
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
	return (1);
}

static int	ft_make_oneline_map_two(char *gnl_line, t_cube *map)
{
	char *tmp;

	if (ft_line_char_check(gnl_line, MAP_CHAR, map) == -1)
		return (-1);
	ft_set_row_col(gnl_line, map);
	tmp = map->m_line;
	map->m_line = ft_cube_strjoin(map->m_line, "@", gnl_line);
	free(tmp);
	if (map == NULL)
		return (-1);
	return (1);
}

static int	ft_line_char_check(char *line, char *base, t_cube *map_info)
{
	unsigned int i;

	i = 0;
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

static void		ft_set_row_col(char *line, t_cube *map)
{
	int max_len;
	
	max_len = ft_strlen(line);
	if (max_len > map->max_col)
		map->max_col = max_len;
	map->max_row += 1;
}
