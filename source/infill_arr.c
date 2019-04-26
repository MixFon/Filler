/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indill_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 13:21:45 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/26 14:39:20 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

/*
** Infill array (bourd and token).
*/

char	**infill_arr(int hieth, int iter)
{
	int		i;
	char	*line;
	char	**arr;

	if (!(arr = (char **)malloc(sizeof(char*) * (hieth + 1))))
		err_sys("Error malloc in infill_arr");
	i = -1;
	while (++i < hieth)
	{
		get_next_line(0, &line);
		arr[i] = ft_strdup(line + iter);
		ft_strdel(&line);
	}
	arr[i] = NULL;
	return (arr);
}

/*
** Parsing width and heith bourd and token.
*/

void	parsing_wh(char *line, int *width, int *heith)
{
	char *fir_num;
	char *sec_num;

	fir_num = NULL;
	sec_num = NULL;
	if (*line == '\0')
		return ;
	while (*line != '\0')
	{
		if (*line == ' ' && ft_isdigit(*(line + 1)) && !sec_num)
			fir_num = (line + 1);
		if (*line == ' ' && ft_isdigit(*(line + 1)) && fir_num)
			sec_num = (line + 1);
		line++;
	}
	*heith = ft_atoi(fir_num);
	*width = ft_atoi(sec_num);
}

/*
** Print bourd.
*/

void	print_arr(char **arr)
{
	while (*arr != NULL)
	{
		write(2, *arr, ft_strlen(*arr));
		write(2, "\n", 1);
		arr++;
	}
}

/*
** Delete arr.
*/

void	dell_arr(char **arr)
{
	while (*arr != NULL)
	{
		free(*arr);
		arr++;
	}
}

/*
** Input error of.
*/

void	err_sys(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
}
