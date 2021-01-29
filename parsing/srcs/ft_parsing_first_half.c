#include "h_parsing.h"

int		ft_first_parsing(char *map_file, t_parsing *map_info)
{
	int		fd;
	int		gnl;
	char	*line;
	
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	gnl = get_next_line(fd, &line);
	while (gnl > 0 && map_info->info_nbr < 8)
	{
		if (ft_try_assigning_value(line, map_info) == -1)
			return (-1);
		gnl = get_next_line(fd, &line);
	}
	printf("\t\t**********FIRST HALF||SUCCESS||****************]\n");
	if (map_info->info_nbr < 8)
		return (-1);
	return (0);
}

int		ft_try_assigning_value(char *line, t_parsing *map_info)
{
	while (*line == ' ' && *line != '\0')
		 line++;
	if (*line == '\0')
		return (0);
	if (ft_strncmp("R ", line, 2) == 0)
		return (ft_assign_resolution(map_info, line + 1));
	if (ft_strncmp("NO ", line, 3) == 0)
		return (ft_text_assign(1, map_info, line + 2));
	if (ft_strncmp("EA ", line, 3) == 0)
		return (ft_text_assign(2, map_info, line + 2));
	if (ft_strncmp("SO ", line, 3) == 0)
		return (ft_text_assign(3, map_info, line + 2));
	if (ft_strncmp("WE ", line, 3) == 0)
		return (ft_text_assign(4, map_info, line + 2));
	if (ft_strncmp("S ", line, 2) == 0)
		return (ft_text_assign(5, map_info, line + 1));
	if (ft_strncmp("F ", line, 2) == 0)
		return (ft_rgb_assign(1, map_info, line + 1));
	if (ft_strncmp("C ", line, 2) == 0)
		return (ft_rgb_assign(2, map_info, line + 1));
	 return (-1);
}

int		ft_assign_resolution(t_parsing *map_info, char *line)
{
	if (map_info->r_bol == 1)
		return (-1);
	map_info->r_bol = 1;
	while (*line == ' ')
		line++;
	if (!ft_isdigit(*line))
		return (-1);
	map_info->r_x = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line == ' ')
		line++;
	if (ft_isdigit(*line) == 0)
		return (-1);
	map_info->r_y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line)
	{
		if (*line != ' ')
			return (-1);
		line++;
	}
	map_info->info_nbr += 1; 
	return (0);
}

void	ft_mapinfo_init(t_parsing *element)
{
	element->r_bol = 0;
	element->r_x = 0;
	element->r_y = 0;
	element->north = NULL;
	element->east = NULL;
	element->south = NULL;
	element->west = NULL;
	element->sprite = NULL;
	element->floor.state = 0;
	element->floor.r = 0;
	element->floor.g = 0;
	element->floor.b = 0;
	element->ceil.state = 0;
	element->ceil.r = 0;
	element->ceil.g = 0;
	element->ceil.b = 0;
	element->info_nbr = 0;
}

void ft_print_mapinfo(t_parsing *element)
{
	printf("r_bol = %d\n", element->r_bol);
	printf("r_x = %d | r_y = %d\n", element->r_x, element->r_y); 
	printf("no = %s \n", element->north); 
	printf("ea = %s \n", element->east);
	printf("so = %s \n", element->south);
	printf("we = %s \n", element->west);
	printf("sprite = %s \n", element->sprite);
	printf("floor.state = %d\n", element->floor.state);
	printf("floor RGB [%d,%d,%d] \n", element->floor.r, element->floor.g, element->floor.b);
	printf("ceiling.state = %d\n", element->ceil.state);
	printf("ceiling RGB [%d,%d,%d] \n", element->ceil.r, element->ceil.g, element->ceil.b);
}

int		ft_check_filename(char *filename, char *ext_name)
{
	unsigned int i;

	i = 0;
	while (filename[i] !='\0')
	{
		if (filename[i] == '.')
		{
			if (filename[i + 1] != '.' && filename[i + 1] != '/')
				break;
		}
		i++;
	}
	if (ft_strcmp(&filename[i], ext_name) == 0)
		return (0);
	printf("Error: not valid file. Use '%s' file\n", ext_name);
	return (1);
}
