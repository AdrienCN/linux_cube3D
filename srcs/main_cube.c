#include "h_cube.h"

typedef		struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}					t_data;

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

int             main(int argc, char **argv)
{
	t_cube		cube;
    void    *mlx;
    void    *mlx_win;
	int		x;
	int		y;
	int		start;
	int		end;
    t_data  img;

	if (argc != 2)
		return (printf("Usage : 1 argument\n"));	
	if (ft_parsing_main(argv[1], &cube))
		return (-1);
	
	cube.floor.rgb = create_trgb(0, cube.floor.r, cube.floor.g, cube.floor.b);
	cube.ceil.rgb = create_trgb(0, cube.ceil.r, cube.ceil.g, cube.ceil.b);

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
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
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
	ft_free_mapinfo(&cube);
	printf("\nmain --> return (0);\n");
	return (0);
}
