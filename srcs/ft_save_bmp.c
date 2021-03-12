/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:10:21 by calao             #+#    #+#             */
/*   Updated: 2021/03/12 11:27:30 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

void		convert_trgb_bmp(t_bmp_color *pixel, t_vars *vars, int x, int y)
{
	int			color;
	char		*dst;

	dst = vars->addr + (y * vars->line_len + x * (vars->bpp / 8));
	color = *(unsigned int*)dst;
	pixel->r = (color & 0xFFFF00) >> 16;
	pixel->g = (color & 0xFF00) >> 8;
	pixel->b = (color & 0xFF);
}

int			get_byte_correction(int win_width)
{
	char	byte_correction[4];
	int		i;
	int		correction_byte;

	byte_correction[0] = 0;
	byte_correction[1] = 3;
	byte_correction[2] = 2;
	byte_correction[3] = 1;
	i = (int)(3 * win_width) % 4;
	correction_byte = byte_correction[i];
	return (correction_byte);
}

int		fill_file_header(t_vars *d, t_file_header *fh)
{
	int		img_calcul;

	img_calcul = (3 * d->win_height * d->win_width)
		+ d->win_height * get_byte_correction(d->win_width);
	ft_bzero(fh, sizeof(t_file_header));
	fh->signature[0] = 'B';
	fh->signature[1] = 'M';
	fh->size = sizeof(t_file_header) - 2 + img_calcul;
	fh->reserved = 0;
	fh->offset_img = sizeof(t_file_header) - 2;
	fh->img.size_img_header = sizeof(t_img_header);
	fh->img.width = d->win_width;
	fh->img.length = d->win_height;
	fh->img.nb_planes = 1;
	fh->img.bpp = 24;
	fh->img.size_img_total = img_calcul;
	return (1);
}

void	fill_img_header(t_vars *vars, t_file_header *fh, int fd, int x)
{
	t_bmp_color		pixel;
	unsigned char	pixel_color[3];
	int				y;
	int				offset;

	offset = get_byte_correction(fh->img.width);
	write(fd, fh, 2);
	write(fd, (char *)(fh) + 4, sizeof(t_file_header) - 4);
	y = fh->img.length - 1;
	while (y > -1)
	{
		x = 0;
		while (x < fh->img.width)
		{
			convert_trgb_bmp(&pixel, vars, x, y);
			pixel_color[0] = pixel.b;
			pixel_color[1] = pixel.g;
			pixel_color[2] = pixel.r;
			write(fd, pixel_color, 3);
			x++;
		}
		ft_bzero(pixel_color, 3);
		write(fd, pixel_color, offset);
		y--;
	}
}

int		ft_save_bmp(t_vars *vars)
{
	int				fd;
	t_file_header	fh;
	int				x;

	fd = open("save.bmp", O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
		return (-1);
	if (fill_file_header(vars, &fh) == 1)
	{
		x = 0;
		fill_img_header(vars->img, &fh, fd, x);
	}
	close(fd);
	if (fd == -1)
		return (-1);
	return (1);
}
