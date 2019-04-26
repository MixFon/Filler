/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:27:00 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/26 14:42:04 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"

# define FINISH ft_printf("%d %d\n", 0, 0);\exit(0);

typedef struct		s_bourd
{
	char			sym;
	char			enemy_sym;
	int				width;
	int				heith;
	char			**bourd;
	int				in_x;
	int				in_y;
	int				cor_en[2];
	int				cor_us[2];
}					t_bourd;

typedef struct		s_clst
{
	int				x_list;
	int				y_list;
	struct s_clst	*next;
	int				sharp;
}					t_clst;

typedef struct		s_token
{
	int				width;
	int				heith;
	char			**token;
	int				coor_x[20];
	int				coor_y[20];
	int				iter;
}					t_token;
/*
** File infill_arr.c
*/
void				parsing_wh(char *line, int *width, int *heith);
char				**infill_arr(int hieth, int iter);
void				print_arr(char **arr);
void				dell_arr(char **arr);
void				err_sys(char *err);
/*
** File add_list.c
*/
void				infill_coor_tok(t_token *tk);
t_token				*create_token(void);
int					check_insert_tok(t_bourd *br, t_token *tk, int i, int j);
t_clst				*creat_clst(void);
t_clst				*add_list(t_clst *list, int i, int j);
/*
** File search_sharp.c
*/
void				delete_list(t_clst *list);
void				move_left_up(t_clst *list, t_bourd *br);
void				move_right_up(t_clst *list, t_bourd *br);
void				move_left_down(t_clst *list, t_bourd *br);
int					search_sharp(t_clst *list, t_bourd *br, t_token *tk);
/*
** File infill_perimetr.c
*/
void				move_right_dowm(t_clst *list, t_bourd *br);
void				search_track(t_clst *list, t_bourd *br, t_token *tk);
void				infil_perimetr(t_bourd *br, int i, int j);
void				start_cor(t_bourd *br, int i, int j);
void				init_start_cor(t_bourd *br);
/*
** File main.c
*/
int					read_bourd(t_bourd *br, t_token *tk);
t_bourd				*read_sym(void);
void				dell(t_bourd *br, t_token *tk);
int					main(void);
void				enemy_perimetr(t_bourd *br);
/*
** File main.c
*/
void				parsing_infillarr(char *line, t_bourd *br);
#endif
