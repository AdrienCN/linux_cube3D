/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:18:20 by calao             #+#    #+#             */
/*   Updated: 2021/03/12 19:07:54 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

int		ft_is_file_readable(char *file_path)
{
	int fd;
	int ret;
	char buf;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	ret = read(fd, &buf, 1);
	if (ret < 0)
		return (-2);
	close(fd);
	if (fd < 0)
		return (-3);
	return (0);
}

void	ft_class_one_error(int error)
{
	if (error == -1)
		printf("could not open .cub or .xpm.\n");
	else if (error == -2)
		printf("could not read from .cub or .xpm.\n");
	else if (error == -3)
		printf("could not close .cub or .xpm.\n");
	else if (error == -4)
		printf("file is not .cub. Verify filename extension.\n");
	else
		printf("well this error is unknown...awkward\n");
}

void	ft_class_two_error(int error)
{
	if (error == -3)
		printf("please verify resolution informations format.\n");
	else if (error == -4)
		printf("please verify texture informations format.\n");
	else if (error == -5)
		printf("please verify C or F [RGB] informations format.\n");
	else if (error == -6)
		printf("missing information to create map.\n");
	else if (error == -7)
		printf("a line could not be assigned to any of the expected value.\n");
	else
		printf("well this error is unknown...awkward\n");

}

void	ft_class_three_error(int error)
{
	printf("map grid : ");
	if (error == -1)
		printf("non authorized character in map grid.\n");
	else if (error == -2)
		printf("map has more than one player.\n");
	else if (error == -3)
		printf("error in map join from char* to char**. Malloc has failed.\n");
	else if (error == -4)
		printf("horizontal empty line found in map grid.\n");
	else if (error == -5)
		printf("map must contain at least 1 row and 1 col.\n");
	else if (error == -6)
		printf("empty line found vertically.\n");
	else if (error == -7)
		printf("wall missing. Map border must '1' only.\n");	
	else if (error == -8)
		printf("0 in contact with void.\n");
	else
		printf("well this error is unknown...awkward\n");
}

int		ft_parsing_error_msg(int class, int error)
{
	printf("class = %d |  error = %d\n", class, error);
	printf("Parsing error: ");
	if (class == 1)
		ft_class_one_error(error);
	if (class == 2)
		ft_class_two_error(error);
	if (class == 3)
		ft_class_three_error(error);
	return (1);
}

int		ft_parsing_main(char *map_file_name, t_cube *cube)
{
	int			fd;
	int			error;

	ft_mapinfo_init(cube);
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
	if ((error = close(fd)) < 0)
		return(ft_parsing_error_msg(1, -3));
	printf("--------------after-------------------\n");
	ft_print_mapinfo(cube);
	printf("----------------------------------\n");
	return (0);
}


void	ft_free_doublearray(char **tab)
{
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

void	ft_free_mapinfo(t_cube *element)
{
	if (element->north != NULL)
		free(element->north);
	if (element->east != NULL)
		free(element->east);
	if (element->south != NULL)
		free(element->south);
	if (element->west != NULL)
		free(element->west);
	if (element->sprite != NULL)
		free(element->sprite);
	if (element->map != NULL)
	{
		ft_free_doublearray(element->map);
		free(element->map);
	}
	if (element->gnl_line != NULL)
		free(element->gnl_line);
	if (element->m_line != NULL)
		free(element->m_line);
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
	element->player_tmp.cardinal = '0';
	element->player_tmp.x = 0;
	element->player_tmp.y = 0;
	element->ceil.state = 0;
	element->ceil.r = 0;
	element->ceil.g = 0;
	element->ceil.b = 0;
	element->map = NULL;
	element->gnl_line = NULL;
	element->m_line = NULL;
	element->map_start = TRUE;
	element->map_end = FALSE;
	element->max_row = 0;
	element->max_col = 0;
	element->info_nbr = 0;
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
		ft_print_tab(element->map);
	}
}

