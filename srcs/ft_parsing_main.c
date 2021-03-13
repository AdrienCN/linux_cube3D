/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:18:20 by calao             #+#    #+#             */
/*   Updated: 2021/03/13 17:16:53 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

int		ft_parsing_main(char *map_file_name, t_cube *cube)
{
	int			fd;
	int			error;

	if ((error = ft_check_file_ext_name(map_file_name, ".cub")))
		return (ft_parsing_error_msg(1, -4));
	if ((error = ft_is_file_readable(map_file_name)))
		return (ft_parsing_error_msg(1, error));
	if ((fd = open(map_file_name, O_RDONLY)) < 0)
		return (ft_parsing_error_msg(1, -1));
	if ((error = ft_first_parsing(fd, cube)))
		return (ft_parsing_error_msg(2, error));
	if ((error = ft_second_parsing(fd, cube)))
		return (ft_parsing_error_msg(3, error));
	printf("--------------after-------------------\n");
	ft_print_mapinfo(cube);
	printf("----------------------------------\n");
	return (0);
}

void ft_print_mapinfo(t_cube *element)
{
	int i;

	printf("r_bol = %d\n", element->r_bol);
	printf("r_x = %d | r_y = %d\n", element->r_x, element->r_y); 
	printf("no = %s \n", element->north); 
	printf("ea = %s \n", element->east);
	printf("so = %s \n", element->south);
	printf("we = %s \n", element->west);
	printf("sprite = %s \n", element->sprite);
	printf("floor.state = %d\n", element->floor.state);
	printf("floor RGB [%d,%d,%d] \n", element->floor.r, element->floor.g, element->floor.b);
	printf("ceiling.state = %d\n", element->ceil.state);
	printf("ceiling RGB [%d,%d,%d] \n", element->ceil.r, element->ceil.g, element->ceil.b);
	printf("_____Player___:\n");
	printf("Orientation = %c | X = %f | Y = %f\n",
		   	element->player_tmp.cardinal, element->player_tmp.x, element->player_tmp.y);
	printf("max_row = %d\n", element->max_row);
	printf("max_col = %d\n", element->max_col);
	printf("m_line = {%s}\n", element->m_line);
	printf("gnl_line = [%s]\n", element->gnl_line);
	printf("sprite_count = %d\n", element->sprite_count);
	if (element->map == NULL)
		printf("element->map = (null)\n");
	else
	{
		printf("______________MAP_______________:\n");
		i = 0;
		printf("col:--|");
		while (i < element->max_col)
		{
			printf("%d|", i);
			i++;
		}
		printf("\n____________________________:\n");
	}
}
