#include "h_cube.h"

static	void	ft_get_sprite_val(t_vars *vars, t_sprite *sprite)
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

static	int		ft_get_sprite_color(t_vars *vars, t_sprite *sprite, int x, int y)
{
	int x_xpm;
	int y_xpm;
	int color;

	x_xpm = x / sprite->width * vars->text.sprite.width;
	y_xpm = y / sprite->height * vars->text.sprite.height;
	color = ft_get_xpm_pixel_value(&vars->text.sprite, x_xpm, y_xpm);
	return (color);
}

static	void	ft_draw_sprite(t_vars *vars, t_sprite *sprite)
{
	int x;
	int y;
	int x_sprite;
	int y_sprite;
	int sprite_color;
	int hide_color;
	
	x = 0;

	x_sprite = 0;
	if (sprite->left_x < 0)
		x_sprite += -sprite->left_x;
	sprite_color = RED;
	hide_color = ft_get_xpm_pixel_value(&vars->text.sprite, 0, 0);
	while (x < vars->win_width)
	{
		y_sprite = 0;
		y = 0;
		while (y < vars->win_height)
		{
			if ((y >= sprite->start_y && y <= sprite->end_y)
					&& (x >= sprite->left_x && x <= sprite->right_x))
			{
				if (sprite->dist < vars->rays[x].distance)
				{
					sprite_color = ft_get_sprite_color(vars, sprite,
							x_sprite, y_sprite);
					if (sprite_color != hide_color)
						my_mlx_pixel_put(vars, x, y, sprite_color);
				}
				y_sprite++;
			}
			y++;
		}
		if (y_sprite)
			x_sprite++;
		x++;
	}
}

static	void	ft_sort_sprite_by_dist(t_vars *vars, t_sprite *sprite)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < vars->sprite_count - 1)
	{
		j = i;
		while (j < vars->sprite_count)
		{
			if (sprite[i].dist < sprite[j].dist)
			{
				tmp = sprite[j];
				sprite[j] = sprite[i];
				sprite[i] = tmp;
				i = 0;
			}
			j++;
		}
		i++;
	}
}

void	ft_render_sprite(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->sprite_count)
	{
		if (vars->sprite_tab[i].is_visible)
			ft_get_sprite_val(vars, &vars->sprite_tab[i]);
		i++;
	}
	ft_sort_sprite_by_dist(vars, vars->sprite_tab);
	i = 0;
	while (i < vars->sprite_count)
	{
		if (vars->sprite_tab[i].is_visible)
			ft_draw_sprite(vars, &vars->sprite_tab[i]);
		i++;
	}
}
