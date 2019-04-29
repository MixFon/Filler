/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:08:34 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/29 12:56:53 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "mlx.h"
# include "../../include/filler.h"
# include <stdio.h>
# include <stdlib.h>

# define ABS(N) ((N<0)?(-N):(N))

/*
** Size windiw.
*/

# define WIDTH		1280
# define HEITH		720
# define INDENT		200

/*
** Keys.
*/

# define ESC		53

/*
** Size rectengle score.
*/

# define W_REC		360
# define H_REC		60

/*
** Colors:
** C_BOURD	- color bourd;
** C_SCORE	- color rectengle score;
** C_BD		- color blue dark;
** C_Bl		- color blue ligth;
** C_P		- color pink;
** C_R		- color red;
*/

# define C_BOURD	"6A4849"
# define C_SCORE	"540f0c"
# define C_BD		"2056B6"
# define C_BL		"2E94E9"
# define C_P		"FF6C98"
# define C_R		"BF2956"

/*
** Path to files .xpm
** Path to background.
*/

# define IMGPATH	"/Users/widraugr/MyFile/File42/Filler/visual/back3.xpm"

typedef struct		s_vis
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_back;
	void			*img_bourd;
	void			*img_obd;
	void			*img_obl;
	void			*img_xr;
	void			*img_xp;
	void			*img_score;
	int				width;
	int				heith;
	int				col;
	int				row;
	char			**map;
	char			**map_xr;
	char			**map_xp;
	char			**map_obd;
	char			**map_obl;
	char			**map_bourd;
	char			**map_score;
	char			name_o[30];
	char			name_x[30];
	int				score_o;
	int				score_x;
	int				x_it;
	int				y_it;
}					t_vis;
/*
** File main.c
*/
char				*last_name(char *name, char *line);
void				get_name_players(t_vis *vis, char *line);
t_vis				*create_vis(void);
int					exit_key(int key, t_vis *vis);
int					main(void);
/*
** File init.c
*/
int					read_input(t_vis *vis);
int					print_bourd(t_vis *vis);
int					init_back(t_vis *vis);
void				init_image(t_vis *vis);
void				init_val(t_vis *vis);
/*
** File put_square.c
*/
void				create_map_square(t_vis *vis);
int					init_image_squer(t_vis *vis);
void				coor_centr(int *x, int *y, int heith, int width);
void				print_score(t_vis *vis);
void				put_square(t_vis *vis, int i, int j);
/*
** File crea_color_map.c
*/
void				new_map(t_vis *vis);
void				rewrite_arr(t_vis *vis);
int					size_square(t_vis *vis);
void				colc_size_squre(t_vis *vis);
char				**crea_color_map(int heith, int width, const char *color);
/*
** File score.c
*/
void				score(char *line, int *score_o, int *score_x);
void				delete_map_square(t_vis *vis);
void				print_fon(t_vis *vis);
int					close_win(void);
#endif
