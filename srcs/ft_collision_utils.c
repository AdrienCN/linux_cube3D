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
	if (item == '1')
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
	if (y >= vars->win_height || y <= 0)
	{
		printf("Y limit is reached\n");
		return (1);
	}
	if (x >= vars->win_width || x <= 0)
	{
		printf("X limit is reached x = %f\n", x);
			return (1);
	}
	return (0);
}
