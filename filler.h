
#ifndef FILLER_H
# define FILLER_H

#include "libft/libft.h"
#include "libft/get_next_line.h"

typedef struct	s_plyer
{
	char		sym;
	int			width;
	int			heith;
	char		**bourd;
	int			in_x;
	int			in_y;
	
}				t_plyer;

typedef struct	s_token
{
	int			width;
	int			heith;
	char		**token;
}				t_token;

#endif
