#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_rgb
{
	int state;
	int r;
	int g;
	int b;
}			t_rgb;

typedef struct s_parsing
{
	int r_bol;
	int r_x;
	int r_y;
	char *north;
	char *east;
	char *west;
	char *south;
	char *sprite;
	t_rgb floor;
	t_rgb ceil;
	int info_nbr;
}				t_parsing;

#endif
