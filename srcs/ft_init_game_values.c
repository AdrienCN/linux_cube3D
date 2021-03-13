/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_game_values.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:32:11 by calao             #+#    #+#             */
/*   Updated: 2021/03/13 21:38:27 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void	ft_perso_init(t_vars *vars)
{
	char	compass;
	float	angle;

	vars->player.cardinal = vars->cube.player_tmp.cardinal;
	compass = vars->player.cardinal;
	vars->player.hze_walk = 0;
	vars->player.vert_walk = 0;
	vars->player.turn = 0;
	vars->player.exit = 0;
	if (compass == 'N')
		angle = M_PI / 2;
	else if (compass == 'W')
		angle = M_PI;
	else if (compass == 'S')
		angle = (3 * M_PI) / 2;
	else
		angle = 0.0;
	vars->player.angle = angle;
	vars->player.x = TILE_SIZE * vars->cube.player_tmp.x + TILE_SIZE / 2;
	vars->player.y = TILE_SIZE * vars->cube.player_tmp.y + TILE_SIZE / 2;
}

int		ft_init_sprite(t_vars *vars, char **map)
{
	int i;
	int j;
	int count;

	vars->sprite_count = vars->cube.sprite_count;
	vars->sprite_tab = malloc(sizeof(t_sprite) * vars->sprite_count);
	if (vars->sprite_tab == NULL)
		return (1);
	i = 0;
	count = 0;
	while (map[i] && count < vars->sprite_count)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				ft_set_sprite_val(&vars->sprite_tab[count], i, j);
				count++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_resolution_init(t_vars *vars, t_cube *cube)
{
	int screen_height;
	int screen_width;

	vars->win_width = cube->r_x;
	vars->win_height = cube->r_y;
	if (vars->bmp_save == 0)
	{
		mlx_get_screen_size(vars->mlx, &screen_width, &screen_height);
		if (screen_height < cube->r_y)
			vars->win_height = screen_height;
		if (screen_width < cube->r_x)
			vars->win_width = screen_width;
	}
}

int		ft_set_basic_vars_val(t_vars *vars, t_cube *cube)
{
	ft_resolution_init(vars, cube);
	vars->ceil_color = create_trgb(0, cube->ceil.r, cube->ceil.g, cube->ceil.b);
	vars->floor_color = create_trgb(0, cube->floor.r,
			cube->floor.g, cube->floor.b);
	ft_perso_init(vars);
	cube->map[(int)cube->player_tmp.y][(int)cube->player_tmp.x] = '0';
	vars->ray_num = vars->win_width;
	vars->rays = malloc(sizeof(t_rays) * vars->win_width);
	if (vars->rays == NULL)
		return (1);
	if (ft_init_sprite(vars, vars->cube.map))
		return (1);
	if (ft_init_xpm_img(vars, &vars->text.north, vars->cube.north)
		|| ft_init_xpm_img(vars, &vars->text.east, vars->cube.east)
		|| ft_init_xpm_img(vars, &vars->text.south, vars->cube.south)
		|| ft_init_xpm_img(vars, &vars->text.west, vars->cube.west)
		|| ft_init_xpm_img(vars, &vars->text.sprite, vars->cube.sprite))
		return (1);
	return (0);
}

int		ft_init_game(t_cube *cube, t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (1);
	if (ft_set_basic_vars_val(vars, cube))
		return (1);
	vars->game.img = mlx_new_image(vars->mlx,
			vars->win_width, vars->win_height);
	if (vars->game.img == NULL)
		return (1);
	vars->game.addr = mlx_get_data_addr(vars->game.img, &vars->game.bpp,
			&vars->game.line_len, &vars->game.endian);
	if (vars->game.addr == NULL)
		return (1);
	if (vars->bmp_save == 0)
	{
		vars->win = mlx_new_window(vars->mlx, vars->win_width,
				vars->win_height, "Adrien_cube");
		if (vars->win == NULL)
			return (1);
	}
	return (0);
}
