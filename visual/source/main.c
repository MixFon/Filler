
#include "../include/visual.h"

char *last_name(char *name, char *line)
{
	int len;
	int i;
	int j;

	j = -1;
	len = ft_strlen(line);
	i = len;
	while(i >= 0)
	{
		if(line[i] == '/' || line[i] == '[')
			break ;
		i--;
	}
	while(++i < len)
		name[++j] = line[i];
	name[j - 1] = '\0';
	return (name);
}

/*
** Get name players.
*/

void	get_name_players(t_vis *vis, char *line)
{
	if(!ft_strncmp(line, "$$$ exec p1", 11))
	{
		last_name(vis->name_o, line);	
		ft_printf("name_o = %s\n", vis->name_o);
	}
	else	if(!ft_strncmp(line, "$$$ exec p2", 11))
	{
		last_name(vis->name_x, line);	
		ft_printf("name_x = %s\n", vis->name_x);
	}
}

/*
** Create new structure and initialise.
*/

t_vis	*create_vis(void)
{
	char	*line;
	t_vis	*vis;

	if(!(vis = (t_vis*)malloc(sizeof(t_vis))))
		return (NULL);
	init_val(vis);
	vis->mlx_ptr = mlx_init();
	vis->win_ptr = mlx_new_window(vis->mlx_ptr, WIDTH, HEITH, "Filler");
	while (get_next_line(0, &line))
	{
		get_name_players(vis, line);
		if(!ft_strncmp(line, "Plateau", 7))
		{
			parsing_wh(line, &vis->col, &vis->row);
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	init_image(vis);
	return (vis);
}

/*
** If pressed key esc close programm.
*/

int		exit_key(int key)
{
	if (key == 65307)
		exit(0);
	return (0);
}

int		main(void)
{
	t_vis	*vis;

	if(!(vis = create_vis()))
		exit(0);
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_back, 0, 0);
	mlx_key_hook(vis->win_ptr, exit_key, (void*)0);
	mlx_loop_hook(vis->mlx_ptr, print_bourd, vis);
	mlx_loop(vis->mlx_ptr);
}
