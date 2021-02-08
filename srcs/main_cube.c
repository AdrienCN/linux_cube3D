#include "h_cube.h"

int		main(int argc, char **argv)
{
	t_cube		map_info;

	if (argc != 2)
		return (printf("Usage : 1 argument\n"));	
	if (ft_parsing_main(argv[1], &map_info) != 1)
		return (-1);
	ft_free_mapinfo(&map_info);
	return (0);
}
