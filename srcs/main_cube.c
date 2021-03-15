/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:29:51 by calao             #+#    #+#             */
/*   Updated: 2021/03/15 13:15:20 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

/*
 *
void		ft_print_mapinfo(t_cube *element)
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
	printf("floor RGB [%d,%d,%d] \n", element->floor.r,
			element->floor.g, element->floor.b);
	printf("ceiling.state = %d\n", element->ceil.state);
	printf("ceiling RGB [%d,%d,%d] \n", element->ceil.r,
			element->ceil.g, element->ceil.b);
	printf("_____Player___:\n");
	printf("Orientation = %c | X = %f | Y = %f\n",
			element->player_tmp.cardinal, element->player_tmp.x,
			element->player_tmp.y);
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

*/

int			ft_parsing_args(t_vars *vars, int argc, char **argv)
{
	vars->bmp_save = 0;
	if (argc < 2 || argc > 3)
	{
		printf("Usage : 1 or 2 arguments\n");
		return (1);
	}
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
		{
			printf("Error: second argument must be \"--save\"\n");
			return (1);
		}
		vars->bmp_save = 1;
	}
	return (0);
}

void		ft_start_game(t_vars *vars)
{
	if (vars->bmp_save)
	{
		ft_cast_all_rays(vars);
		ft_render_sprite(vars);
		ft_save_bmp(vars);
	}
	else
	{
		mlx_hook(vars->win, 33, 1L << 17, &mlx_loop_end, vars->mlx);
		mlx_hook(vars->win, 2, 1L << 0, ft_update_move, vars);
		mlx_hook(vars->win, 3, 1L << 1, ft_reset_player, vars);
		mlx_loop_hook(vars->mlx, ft_update_screen, vars);
		mlx_loop(vars->mlx);
	}
}

int			main(int argc, char **argv)
{
	t_vars		vars;

	ft_game_null_init(&vars);
	if (ft_parsing_args(&vars, argc, argv)
			|| ft_parsing_main(argv[1], &vars.cube))
	{
		ft_free_game(&vars);
		return (-1);
	}
	if (ft_init_game(&vars.cube, &vars))
	{
		ft_free_game(&vars);
		printf("Error while initializing game structures.\n");
		return (-1);
	}
	ft_start_game(&vars);
	ft_free_game(&vars);
	printf("\nmain --> return (0);\n");
	return (0);
}

int			ft_update_screen(t_vars *vars)
{
	ft_cast_all_rays(vars);
	ft_render_sprite(vars);
	ft_render_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->game.img, 0, 0);
	ft_reset_sprites_visibility(vars, vars->sprite_count);
	return (0);
}
