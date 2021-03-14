/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:18:20 by calao             #+#    #+#             */
/*   Updated: 2021/03/14 01:44:25 by calao            ###   ########.fr       */
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
	return (0);
}
