
#ifndef VISUAL_H
# define VISUAL_H

#include "minilibx/mlx.h"
#include "../filler.h"
#include <stdio.h>
#include <stdlib.h>

# define ABS(N) ((N<0)?(-N):(N))

# define WIDTH 1024
# define HEITH 768

typedef struct	s_vis
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_back;
	void		*img_bourd;
	void		*img_obd;
	void		*img_obl;
	void		*img_xr;
	void		*img_xp;
	int			heith;
	int			width;
	int			col;
	int			row;
	char		**map;
	char		**map_xr;
	char		**map_xp;
	char		**map_obd;
	char		**map_obl;
	char		**map_bourd;
}				t_vis;
#endif

