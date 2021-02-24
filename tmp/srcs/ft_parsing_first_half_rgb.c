#include "h_cube.h"

int		ft_rgb_val(t_rgb *ceiloor, char *line)
{
	int count;

	count = 0;
	if (ceiloor->state == 1)
		return (-1);
	ceiloor->state = 1;
	while (count < 3)
	{
		while (*line == ' ' || *line == ',')
			line++;
		if (count == 0)
			ceiloor->r = ft_atoi(line);
		else if (count == 1)
			ceiloor->g = ft_atoi(line);
		else if (count == 2)
			ceiloor->b = ft_atoi(line);
		line += 3;
		count++;
	}
	return (0);
}

int		ft_rb_format(char *line)
{
	int count;
	int number;

	count = 0;
	number = 0;
	while (*line  != '\0' && count < 2)
	{
		if (ft_isdigit(*line))
		{
			if (number >= 2 || ft_atoi(line) < 0 || ft_atoi(line) > 255)
				return (-1);
			while (ft_isdigit(*line))
				line++;
			number++;
		}
		if (*line == ',')
			count++;
		if (*line != ',' && ft_isdigit(*line) != 1 && *line != ' ')
			return (-1);
		line++;
	}
	if (*line != '\0' && count == 2 && number == 2)
		return (0);
	return (-1);
}

int		ft_b_format(char *line)
{
	int tmp;

	while (*line == ' ' && *line != '\0')
		line++;
	if (*line == '\0' || !ft_isdigit(*line))
		return (-1);
	tmp = ft_atoi(line);
	if (tmp < 0 || tmp > 255)
		return (-1);
	while (ft_isdigit(*line))
			line++;
	while (*line != '\0')
	{
		if (*line != ' ')
			return (-1);
		line++;
	}
	return (0);
}

int		ft_check_rgb_format(char *line)
{
	int count;

	count = 0;
	if (ft_rb_format(line) == -1)
		return (-1);
	while (count < 2)
	{
		if (*line == ',')
			count++;
		line++;
	}
	if (ft_b_format(line) == -1)
		return (-1);
	return (0);
}

int		ft_rgb_assign(int arrow, t_cube *map_info, char *line)
{
	if (ft_check_rgb_format(line) == -1)
		return (-1);
	map_info->info_nbr += 1;
	if (arrow == 1)
		return(ft_rgb_val(&(map_info->floor), line));
	else if (arrow == 2)
		return(ft_rgb_val(&(map_info->ceil), line));
	return (-1);
}
