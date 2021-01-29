/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cube3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:18:20 by calao             #+#    #+#             */
/*   Updated: 2021/01/29 16:18:51 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parsing.h"

int		main(int argc, char **argv)
{
	char		*map_file;
	t_parsing	map_info;

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
	if (ft_first_parsing(map_file, &map_info) == -1)
	{
		printf("Before quiting. Map_info = \n");
		ft_print_mapinfo(&map_info);
		return(1);
	}
	printf("--------------after-------------------\n");
	ft_print_mapinfo(&map_info);
	printf("----------------------------------\n");

//	ft_free_mapinfo(map_info);
	return (0);
}

