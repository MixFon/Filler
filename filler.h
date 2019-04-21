/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:27:00 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/09 14:51:35 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft/ft_printf.h"
# include "libft/get_next_line.h"

# define FINISH ft_printf("%d %d\n", 0, 0);\
				exit(0);


typedef struct	s_bourd
{
	char			sym;
	char			enemy_sym;
	int				width;
	int				heith;
	char			**bourd;
	int				in_x;
	int				in_y;
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

void	parsing_wh(char *line, int *width, int *heith);
char	**infill_arr(int hieth, int iter);
void	print_arr(char **arr);
void	dell_arr(char **arr);

#endif
