/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 17:14:38 by calao             #+#    #+#             */
/*   Updated: 2021/03/13 17:16:41 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void			ft_game_null_init(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->rays = NULL;
	vars->sprite_tab = NULL;
	vars->game.addr = NULL;
	vars->game.img = NULL;
	vars->text.north.addr = NULL;
	vars->text.north.img = NULL;
	vars->text.east.addr = NULL;
	vars->text.east.img = NULL;
	vars->text.south.addr = NULL;
	vars->text.south.img = NULL;
	vars->text.west.addr = NULL;
	vars->text.west.img = NULL;
	vars->text.sprite.addr = NULL;
	vars->text.sprite.img = NULL;
	ft_cube_null_init(&vars->cube);
}

int			ft_init_xpm_img(t_vars *vars, t_img *img, char *img_path)
{
	img->img = mlx_xpm_file_to_image(vars->mlx, img_path,
				&img->width, &img->height);
	if (img->img == NULL)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, 
			&img->line_len, &img->endian);
	if (img->addr == NULL)
		return (1);
	return (0);
}

void	ft_set_sprite_val(t_sprite *sprite, int i, int j)
{
				sprite->id = 2;
				sprite->is_visible = 0;
				sprite->dist = -1;
				sprite->row = i;
				sprite->col = j;
				sprite->x = j * TILE_SIZE + (TILE_SIZE / 2);
				sprite->y = i * TILE_SIZE + (TILE_SIZE / 2);
}

void	ft_cube_null_init(t_cube *element)
{
	//Supprimer les int qui ne sont pas des BOL ? sauf sprite count?
	element->sprite_count = 0;
	element->r_bol = 0;
	element->r_x = 0;
	element->r_y = 0;
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
	element->map_start = TRUE;
	element->map_end = FALSE;
	element->max_row = 0;
	element->max_col = 0;
	element->gnl_leak_proof = NULL;
	element->map = NULL;
	element->gnl_line = NULL;
	element->m_line = NULL;
	element->north = NULL;
	element->east = NULL;
	element->south = NULL;
	element->west = NULL;
	element->sprite = NULL;
	element->info_nbr = 0;
}

