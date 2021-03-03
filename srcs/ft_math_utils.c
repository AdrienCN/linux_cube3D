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

float	ft_radconvert(float degree)
{
	float rad;

	rad = degree * M_PI / 180;
	return (rad);
}

float	ft_get_distance(float x1, float y1, float x2, float y2)
{
	double result;
	double x;
	double y;

	x = (x2 - x1) * (x2 - x1);
	y = (y2 - y1) * (y2 - y1);

	result = sqrt(x + y);
	return ((float)result);
}

