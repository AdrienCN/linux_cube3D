#include "h_cube.h"

typedef		struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}					t_data;

typedef		struct s_vars
{
	void	*mlx;
	void	*win;
}					t_vars;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	else
		printf("key_pressed = %d|\n", keycode);
}

int             main(int argc, char **argv)
{
	t_cube		cube;
	t_vars		vars;
    /*
	t_data		img;
	int		x;
	int		y;
	int		start;
	int		end;
	*/
	if (argc != 2)
		return (printf("Usage : 1 argument\n"));	
	if (ft_parsing_main(argv[1], &cube))
		return (-1);
	
	cube.floor.rgb = create_trgb(0, cube.floor.r, cube.floor.g, cube.floor.b);
	cube.ceil.rgb = create_trgb(0, cube.ceil.r, cube.ceil.g, cube.ceil.b);

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920 / 2,  1080 / 2, argv[1]);
    /*
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len,
                                 &img.endian);
	y = 1080;
	start = 0;
	end = 1920;
	while (y > 0)
	{
		x = 0;
		while (start + x < end)
		{
			my_mlx_pixel_put(&img, x + start, y, 0x00FF00FF);
			x++;
		}
		start ++;
		end--;
		y--;
	}
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    */
	mlx_hook(vars.win, 02, 1L<<0, key_hook,  &vars);
	mlx_loop(vars.mlx);
	ft_free_mapinfo(&cube);
	printf("\nmain --> return (0);\n");
	return (0);
}
