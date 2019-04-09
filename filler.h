/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:27:00 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/09 11:55:44 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include "libft/libft.h"
#include "libft/get_next_line.h"

typedef struct	s_bourd
{
	char			sym;
	char			enemy_sym;
	int				width;
	int				heith;
	char			**bourd;
	int				in_x;
	int				in_y;
	int				sym_x[2];
	int				sym_o[2];
}					t_bourd;

typedef struct		s_clst
{
	int				x_list;
	int				y_list;
	struct s_clst	*next;
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

#endif
