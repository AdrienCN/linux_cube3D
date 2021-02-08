#include "h_cube.h"

int		main(int argc, char **argv)
{
	t_cube		map_info;
	void		*mlx;
	void		*mlx_win;

	if (argc != 2)
		return (printf("Usage : 1 argument\n"));	
	if (ft_parsing_main(argv[1], &map_info))
		return (-1);
	printf("parsing ok\n");
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, map_info.r_x, map_info.r_y, argv[1]);
	(void)mlx_win;
	ft_free_mapinfo(&map_info);
	printf("\nmain --> return (0);\n");
	return (0);
}
