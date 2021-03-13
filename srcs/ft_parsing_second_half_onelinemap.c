/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_onelinemap.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:54:38 by calao             #+#    #+#             */
/*   Updated: 2021/03/13 12:08:43 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static void		ft_set_row_col(char *line, t_cube *map);
static int	ft_make_oneline_map_two(char *gnl_line, t_cube *map);
static char	*ft_cube_strjoin(char const *s1, char const *sep, char const *s2);
static int	ft_line_char_check(char *line, char *base, t_cube *map_info);

int		ft_make_oneline_map(int fd, t_cube *cube)
{
	char	*line;
	int		error;

	while (get_next_line(fd, &cube->gnl_line, &cube->gnl_leak_proof) > 0)
	{
		line = cube->gnl_line;
		if (cube->map_start == TRUE && ft_empty_line(line) == FALSE)
			cube->map_start = FALSE;
		if (cube->map_start == FALSE && cube->map_end == FALSE)
		{
			if (ft_empty_line(line) == TRUE)
				cube->map_end = TRUE;
			else if ((error = ft_make_oneline_map_two(line, cube)))
				return (error);
		}
		else if (cube->map_end == TRUE && ft_empty_line(line) == FALSE)
			return (-4);
		free(line);
	}
	if (cube->max_col == 0 || cube->max_row == 0)
		return (-5);
	return (0);
}

static int	ft_make_oneline_map_two(char *gnl_line, t_cube *map)
{
	char	*tmp;
	int		error;

	if ((error = ft_line_char_check(gnl_line, MAP_CHAR, map)))
		return (error);
	ft_set_row_col(gnl_line, map);
	tmp = map->m_line;
	map->m_line = ft_cube_strjoin(map->m_line, "@", gnl_line);
	free(tmp);
	if (map == NULL)
		return (-3);
	return (0);
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
			if (map_info->player_tmp.cardinal == '0')
			{
				map_info->player_tmp.cardinal = line[i];
				map_info->player_tmp.x = i;
				map_info->player_tmp.y = map_info->max_row;
			}
			else
				return (-2);
		}
		i++;
	}
	return (0);
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
