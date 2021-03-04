#include "h_cube.h"

float	ft_calculate_new_x(float x, t_vars *vars)
{
	float x_ref;
	float angle;

	x_ref = vars->player.x;
	angle = vars->player.angle;

	if (vars->player.vert_walk == 1)
		x = x_ref + cos(angle) * MOVE_SPEED;
	else if (vars->player.vert_walk == -1)
		x = x_ref - cos(angle) * MOVE_SPEED;
	else if (vars->player.hze_walk == 1)
		x = x_ref + cos(ft_within_twopi(angle + (M_PI / 2)))
			* MOVE_SPEED;
	else if (vars->player.hze_walk == -1)
		x = x_ref - cos(ft_within_twopi(angle + (M_PI / 2)))
			* MOVE_SPEED;
	return (x);
}

float ft_calculate_new_y(float y, t_vars *vars)
{
	float y_ref;
	float angle;

	y_ref = vars->player.y;
	angle = vars->player.angle;

	if (vars->player.vert_walk == 1)
		y = y_ref - sin(angle) * MOVE_SPEED;
	else if (vars->player.vert_walk == -1)
		y = y_ref + sin(angle) * MOVE_SPEED;
	else if (vars->player.hze_walk == 1)
		y = y_ref - sin(ft_within_twopi(angle + (M_PI / 2)))
			* MOVE_SPEED;
	else if (vars->player.hze_walk == -1)
		y = y_ref + sin(ft_within_twopi(angle + (M_PI / 2)))
			* MOVE_SPEED;
	return (y);
}

int		ft_update_player(t_vars *vars)
{
	float x;
	float y;

	x = 0;
	y = 0;
	vars->player.angle = ft_within_twopi(vars->player.angle
			+ vars->player.turn * ROT_SPEED);
	x = ft_calculate_new_x(x, vars);
	y = ft_calculate_new_y(y, vars);
	if (ft_is_maplimit(x, y, vars) || ft_map_content(x, y, vars))
			return (1);
	vars->player.x = x;
	vars->player.y = y;
	//printf("x = %f | y = %f* | ", x, y);
	//printf("player_angle = %f\n", vars->player.angle);
	return (0);
}

int		ft_update_move(int keycode, t_vars *vars)
{
	int c;

	c = keycode;
	if (c == A)
		vars->player.hze_walk = 1;
	else if (c == D)
		vars->player.hze_walk = -1;
	else if (c == W)
		vars->player.vert_walk = 1;
	else if (c == S)
		vars->player.vert_walk = -1;
	else if (c == LEFT_ARROW)
		vars->player.turn = 1;
	else if (c == RIGHT_ARROW)
		vars->player.turn = -1;
	//printf("key_pressed = %d|\n", keycode);
	ft_update_player(vars);
	return (1);
}

int				ft_reset_player(int keycode, t_vars *vars)
{
	(void)keycode;
	vars->player.hze_walk = 0;
	vars->player.vert_walk = 0;
	vars->player.turn = 0;
	return (0);
}
