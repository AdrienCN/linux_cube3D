/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:01:42 by calao             #+#    #+#             */
/*   Updated: 2021/03/15 14:47:43 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

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
	else if (error == -8)
		printf("a texture file does not exit or is not readable.\n");
	else if (error == -9)
		printf("resolution values are too low.Min height: 2, min width: 2.\n");
	else
		printf("well this error is unknown...awkward\n");
}

void	ft_class_three_error(int error)
{
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
	else if (error == -9)
		printf("missing player in map grid.\n");
	else
		printf("well this error is unknown...awkward\n");
}

int		ft_parsing_error_msg(int class, int error)
{
	printf("Error\n");
	printf("Parsing: ");
	if (class == 1)
		ft_class_one_error(error);
	if (class == 2)
		ft_class_two_error(error);
	if (class == 3)
		ft_class_three_error(error);
	return (1);
}
