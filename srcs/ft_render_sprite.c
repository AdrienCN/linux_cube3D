#include "h_cube.h"

void	ft_set_sprite_val(t_vars *vars, t_sprite *sprite)
{
	float	screen_dist;

	screen_dist =  (vars->win_width / 2) / tan(ft_radconvert(FOV / 2));
	sprite->angle = vars->player.angle;
	sprite->angle += atan2(sprite->y - vars->player.y,
		   sprite->x - vars->player.x);
	sprite->angle = ft_within_twopi(sprite->angle);
	sprite->dist = ft_get_distance(vars->player.x, vars->player.y,
		   sprite->x, sprite->y);
	sprite->height = (TILE_SIZE / sprite->dist) * screen_dist;
	sprite->width = sprite->height;
	sprite->start_y = (vars->win_height / 2) - (sprite->height / 2);
	if (sprite->start_y < 0)
		sprite->start_y = 0;
	sprite->end_y = (vars->win_height / 2) + (sprite->height / 2);
	if (sprite->end_y > vars->win_height)
		sprite->end_y = vars->win_height;
	sprite->left_x = (vars->win_width / 2) + tan(sprite->angle) * screen_dist;
	sprite->left_x -= sprite->width / 2;

	sprite->right_x = sprite->left_x + sprite->width;
}

void	ft_draw_sprite(t_vars *vars, t_sprite *sprite)
{
	int x;
	int y;
	
	x = 0;
	while (x < vars->win_width)
	{
		y = 0;
		while (y < vars->win_height)
		{
			if ((y >= sprite->start_y && y <= sprite->end_y)
					&& (x >= sprite->left_x && x <= sprite->right_x))
			{
				if (sprite->dist < vars->rays[x].distance)
					my_mlx_pixel_put(vars, x, y, RED);
			}
			y++;
		}
		x++;
	}
}

void	ft_render_sprite(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->sprite_count)
	{
		if (vars->sprite_tab[i].is_visible)
		{
			ft_set_sprite_val(vars, &vars->sprite_tab[i]);
			ft_draw_sprite(vars, &vars->sprite_tab[i]);
		}
		i++;
	}
}

