#include "h_cube.h"


int		ft_map_content(float x, float y, t_vars *vars)
{
	if (ft_is_wall(x, y, vars) == 1)
		return (1);
	else if (ft_is_sprite(x, y, vars))
		return (2);
	else
		return (0);
}

int		ft_is_wall(float x, float y, t_vars *vars)
{
	int row;
	int col;
	char item;

	row =  y / vars->tile_height;
	col = x / vars->tile_width;
	
	item = vars->cube.map[row][col];
	if (item == '1' || item == ' ')
		return (1);
	return (0);
}

int		ft_is_sprite(float x, float y, t_vars *vars)
{
	int row;
	int col;
	char item;

	row =  y / vars->tile_height;
	col = x / vars->tile_width;

	item = vars->cube.map[row][col];
	if (item == '2')
		return (1);
	return (0);
}

int		ft_is_maplimit(float x, float y, t_vars *vars)
{
	float map_limit_y;
	float map_limit_x;

	map_limit_x = TILE_SIZE * vars->cube.max_col;
	map_limit_y = TILE_SIZE * vars->cube.max_row;

	if (y >= map_limit_y || y <= 0)
		return (1);
	if (x >= map_limit_x|| x <= 0)
		return (1);
	return (0);
}
