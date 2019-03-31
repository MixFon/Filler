
#ifndef FILLER_H
# define FILLER_H

#include "libft/libft.h"
#include "libft/get_next_line.h"

typedef struct	s_bourd
{
	char		sym;
	int			width;
	int			heith;
	char		**bourd;
	int			in_x;
	int			in_y;
	
}				t_bourd;

typedef struct	s_token
{
	int			width;
	int			heith;
	char		**token;
	int			coor_x[20];
	int			coor_y[20];
	int			iter;
}				t_token;

#endif
