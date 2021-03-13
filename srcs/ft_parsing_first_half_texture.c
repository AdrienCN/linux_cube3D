/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_first_half_texture.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:48:46 by calao             #+#    #+#             */
/*   Updated: 2021/03/13 21:48:47 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

int		ft_text_give_val(char **text, char *path)
{
	if (*text != NULL)
	{
		free(path);
		return (-4);
	}
	*text = path;
	return (0);
}

int		ft_text_assign(int arrow, t_cube *map_info, char *line)
{
	char	*path;

	if (ft_text_check_format(line))
		return (-4);
	printf("texture _format ok\n");
	path = ft_text_check_path(line);
	if (path == NULL)
		return (-8);
	map_info->info_nbr += 1;
	if (arrow == 1)
		return (ft_text_give_val(&map_info->north, path));
	else if (arrow == 2)
		return (ft_text_give_val(&map_info->east, path));
	else if (arrow == 3)
		return (ft_text_give_val(&map_info->south, path));
	else if (arrow == 4)
		return (ft_text_give_val(&map_info->west, path));
	else if (arrow == 5)
		return (ft_text_give_val(&map_info->sprite, path));
	return (-4);
}

int		ft_text_check_format(char *path)
{
	while (*path == ' ')
		path++;
	if (*path == '\0')
		return (1);
	while (*path != '\0' && *path != ' ')
	{
		if (ft_isprint(*path) == 0)
			return (1);
		path++;
	}
	while (*path != '\0')
	{
		if (*path != ' ')
			return (1);
		path++;
	}
	return (0);
}

char	*ft_text_check_path(char *path)
{
	char	*stock;
	int		i;

	i = 0;
	while (*path == ' ')
		path++;
	while (path[i] != '\0' && path[i] != ' ')
		i++;
	if ((stock = ft_strndup(path, i)) == NULL)
		return (NULL);
	if (ft_check_file_ext_name(stock, ".xpm"))
	{
		free(stock);
		return (NULL);
	}
	if (ft_is_file_readable(stock))
	{
		free(stock);
		return (NULL);
	}
	return (stock);
}
