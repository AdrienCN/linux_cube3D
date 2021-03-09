/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_game_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 09:30:49 by calao             #+#    #+#             */
/*   Updated: 2021/03/09 16:10:50 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

int				ft_reset_player(int keycode, t_vars *vars)
{
	(void)keycode;
	vars->player.hze_walk = 0;
	vars->player.vert_walk = 0;
	vars->player.turn = 0;
	return (0);
}

void		ft_reset_sprites(t_vars *vars, int sprite_count)
{
	int i;

	i = 0;
	while (i < sprite_count)
	{
		vars->sprite_tab[i].is_visible = 0;
		vars->sprite_tab[i].dist = -1;
		i++;
	}
}


