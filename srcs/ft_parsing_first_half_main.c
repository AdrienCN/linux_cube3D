#include "h_cube.h"


int		ft_first_parsing(int fd, t_cube *cube)
{
	char	*line;
	int		error;

	while (get_next_line(fd, &line, &cube->gnl_leak_proof) > 0 
			&& cube->info_nbr < 8)
	{
		if ((error = ft_try_assigning_value(line, cube)))
		{
			free(line);
			return (error);
		}
		free(line);
	}
	free(line);
	if (cube->info_nbr < 8)
		return (-6);
	return (0);
}

int		ft_try_assigning_value(char *line, t_cube *cube)
{
	while (*line == ' ' && *line != '\0')
		 line++;
	if (*line == '\0')
		return (0);
	if (ft_strncmp("R ", line, 2) == 0)
		return (ft_assign_resolution(cube, line + 1));
	if (ft_strncmp("NO ", line, 3) == 0)
		return (ft_text_assign(1, cube, line + 2));
	if (ft_strncmp("EA ", line, 3) == 0)
		return (ft_text_assign(2, cube, line + 2));
	if (ft_strncmp("SO ", line, 3) == 0)
		return (ft_text_assign(3, cube, line + 2));
	if (ft_strncmp("WE ", line, 3) == 0)
		return (ft_text_assign(4, cube, line + 2));
	if (ft_strncmp("S ", line, 2) == 0)
		return (ft_text_assign(5, cube, line + 1));
	if (ft_strncmp("F ", line, 2) == 0)
		return (ft_rgb_assign(1, cube, line + 1));
	if (ft_strncmp("C ", line, 2) == 0)
		return (ft_rgb_assign(2, cube, line + 1));
	 return (-7);
}

int		ft_assign_resolution(t_cube *map_info, char *line)
{
	if (map_info->r_bol == 1)
		return (-3);
	map_info->r_bol = 1;
	while (*line == ' ')
		line++;
	if (!ft_isdigit(*line))
		return (-3);
	map_info->r_x = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line == ' ')
		line++;
	if (ft_isdigit(*line) == 0)
		return (-3);
	map_info->r_y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line)
	{
		if (*line != ' ')
			return (-3);
		line++;
	}
	map_info->info_nbr += 1; 
	return (0);
}
