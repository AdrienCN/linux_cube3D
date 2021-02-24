#include "h_cube.h"

float		ft_within_twopi(float rad)
{
	float rad2;

	rad2 = rad;
	while (rad2 >= (2 * M_PI))
		rad2 -= 2 * M_PI;
	while (rad2 < 0)
		rad2 += 2 * M_PI;
	return (rad2);
}

float	ft_degree_to_rad(float degree)
{
	float rad;

	rad = degree * M_PI / 180;
	return (rad);
}
