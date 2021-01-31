/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cube3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:18:20 by calao             #+#    #+#             */
/*   Updated: 2021/01/31 10:09:24 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"

int		main(int argc, char **argv)
{
	char		*map_file;
	t_cube	map_info;
	int			fd;

	if (argc != 2)
	{
		printf("Usage : 1 argument\n");
		return (-1);
	}
	map_file = argv[1];
	if (ft_check_filename(map_file, ".cub"))
		return (-1);
	ft_mapinfo_init(&map_info);
	printf("----------------------------------\n");
	ft_print_mapinfo(&map_info);
	printf("----------------------------------\n");
	fd = open(map_file, O_RDONLY);
	if (fd < 0 || ft_first_parsing(fd, &map_info) == -1
			|| ft_second_parsing(fd, &map_info) == -1)
	{
		printf("...ERROR....Map_info value: \n");
		ft_print_mapinfo(&map_info);
		printf("\n...program SHUT DOWN...\n");
		return(1);
	}
	printf("--------------after-------------------\n");
	ft_print_mapinfo(&map_info);
	printf("----------------------------------\n");

//	ft_free_mapinfo(map_info);
	return (0);
}

void	ft_mapinfo_init(t_cube *element)
{
	element->r_bol = 0;
	element->r_x = 0;
	element->r_y = 0;
	element->north = NULL;
	element->east = NULL;
	element->south = NULL;
	element->west = NULL;
	element->sprite = NULL;
	element->floor.state = 0;
	element->floor.r = 0;
	element->floor.g = 0;
	element->floor.b = 0;
	element->ceil.state = 0;
	element->ceil.r = 0;
	element->ceil.g = 0;
	element->ceil.b = 0;
	element->player = '0';
	element->map = NULL;
	element->info_nbr = 0;
}

void ft_print_mapinfo(t_cube *element)
{
	int i;
	int y;

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
	printf("Player_Orientation = %c\n", element->player);
	if (element->map == NULL)
		printf("element->map = (null)\n");
	else
	{
		printf("______________MAP_______________:\n");
		i = 0;
		while (element->map[i])
		{
			y = 0;
			while (element->map[i][y] != '\0')
			{
				printf("%c", element->map[i][y]);
				y++;
			}
			printf("\n");
			i++;
		}
	}
}

