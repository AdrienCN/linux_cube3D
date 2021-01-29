#include "h_parsing.h"

int		ft_text_give_val(char **text, char *path)
{
	if (*text != NULL)
	{
		free(path);
		return (-1);
	}
	*text = path;
	return (1);
}

int		ft_text_assign(int arrow, t_parsing *map_info, char *line)
{
	char	*path;
	
	printf("\nassiging line \t\t--[%s]--\n", line);
	if (ft_text_check_format(line) == -1)
		return (-1);
	path = ft_text_check_path(line);
	printf("\t||path ==> %s\n", path);
	if (path == NULL)
		return (-1);
	map_info->info_nbr += 1;
	if (arrow == 1)
		return(ft_text_give_val(&map_info->north, path));
	else if (arrow == 2)
		return(ft_text_give_val(&map_info->east, path));
	else if (arrow == 3)
		return(ft_text_give_val(&map_info->south, path));
	else if (arrow == 4 )
		return(ft_text_give_val(&map_info->west, path));
	else if (arrow == 5)
		return(ft_text_give_val(&map_info->sprite, path));
	return (-1);
}


int		ft_text_check_format(char *path)
{
	while (*path == ' ')
		path++;
	if (*path == '\0')
		return (-1);
	while (*path != '\0' && *path != ' ')
	{
		if (ft_isprint(*path) == 0)
			return (-1);
		path++;
	}
	while (*path != '\0')
	{
		if (*path != ' ')
			return (-1);
		path++;
	}
	return (0);
}

char 	*ft_text_check_path(char *path)
{
	char	*stock;
	int		i;

	i = 0;
	while (*path == ' ')
		path++;
	while (path[i] != '\0' && path[i] != ' ')
		i++;
	stock = ft_strndup(path, i);
	i = open(stock, O_RDONLY);
	if (stock == NULL || ft_check_filename(stock, ".xpm") == -1
			|| i < 0 || close(i) < 0)
	{
		printf("Error closing or opening : %s\n", stock);
		free(stock);
		return (NULL);
	}
	return (stock);
}

