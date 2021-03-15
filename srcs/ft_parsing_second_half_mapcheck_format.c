/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_half_mapcheck_format.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:58:55 by calao             #+#    #+#             */
/*   Updated: 2021/03/15 13:10:22 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static int	ft_emptyline_vert_check(char **map)
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

static int	ft_wall_closed_hze_check(char **map, int max_col)
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
			return (1);
		while (k >= 0 && map[i][k] == ' ')
			k--;
		if (k < 0 || map[i][k] != '1')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_wall_closed_vert_check(char **map, int max_row)
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

static int	ft_zero_in_void_check(char **map, t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '2')
				cube->sprite_count++;
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

int			ft_check_fullmap_format(char **map, t_cube *cube)
{
	if (ft_emptyline_vert_check(map))
		return (-6);
	if (ft_wall_closed_hze_check(map, cube->max_col)
			|| ft_wall_closed_vert_check(map, cube->max_row))
		return (-7);
	if (ft_zero_in_void_check(map, cube))
		return (-8);
	return (0);
}
