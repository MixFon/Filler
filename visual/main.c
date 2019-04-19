
#include "visual.h"

void	new_map(t_vis *vis)
{
	int i;

	i = -1;
	vis->map = (char **)malloc(sizeof(char*) * (vis->row + 1));
	while (++i < vis->row)
		vis->map[i] = ft_strnew(vis->col);
	vis->map[i] = NULL;
}

void	score(char *line, int *score_o, int *score_x)
{
	while (*line != '\0')
	{
		if(*line == 'o')
			*score_o = *score_o + 1;
		if(*line == 'x')
			*score_x = *score_x + 1;
		line++;
	}
}

/*
**  Rewrite bourd. No malloc.
*/

void	rewrite_arr(t_vis *vis)
{
	int		i;
	char	*line;

	if (vis->map == NULL)
		new_map(vis);
	i = -1;
	while (++i < vis->row)
	{
		get_next_line(0, &line);
		score(line, &vis->score_o, &vis->score_x);
		ft_strcpy(vis->map[i], line + 4);
		ft_strdel(&line);
	}
	vis->map[i] = NULL;
}

char	**crea_color_map(int heith, int width, const char *color)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) * (heith + 3));
	map[0] = ft_multi_strdup(4, ft_itoa(width), " ", ft_itoa(heith), " 1 1 "); 
	ft_printf("s = {%s}\n", map[0]);
	map[1] = ft_multi_strdup(2, "b c #", color);
	ft_printf("s = {%s}\n", map[1]);
	i = 1;
	while (++i < heith + 2)
	{
		j = -1;
		map[i] = ft_strnew(width + 1);
		while (++j < width)
			map[i][j] = 'b';
		ft_printf("i = %d s = {%s}\n",i,  map[i]);
	}
	map[i] = NULL;
	return (map);
}

int		size_square(t_vis *vis)
{
	int i;

	i = -1;
	while(++i < 20)
	{
		if (((HEITH - INDENT) <= vis->row * i)
				|| ((WIDTH - INDENT) <= vis->col * i))
			break ;
	}
	if(i < 1)
		return (1);
	return (i);
}

void	colc_size_squre(t_vis *vis)
{
	ft_printf("square size = %d\n", size_square(vis));
	vis->heith = size_square(vis);
	vis->width = vis->heith;
}

/*
** Init image size 10x10.
*/

int		init_image_squer(t_vis *vis)
{
	int a = 0;
	int b = 0;

	colc_size_squre(vis);
	vis->map_score = crea_color_map(60, 200, "540f0c");
	if(!(vis->img_score = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_score, &a, &b)))
		return (0);
	vis->map_bourd = crea_color_map(vis->heith, vis->width, "6A4849");
	if(!(vis->img_bourd = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_bourd, &vis->heith, &vis->width)))
		return (0);
	vis->map_obd = crea_color_map(vis->heith, vis->width, "2056B6");
	if(!(vis->img_obd = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_obd, &vis->heith, &vis->width)))
		return (0);
	vis->map_obl = crea_color_map(vis->heith, vis->width, "2E94E9");
	if(!(vis->img_obl = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_obl, &vis->heith, &vis->width)))
		return (0);
	vis->map_xp = crea_color_map(vis->heith, vis->width, "FF6C98");
	if(!(vis->img_xp = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_xp, &vis->heith, &vis->width)))
		return (0);
	vis->map_xr = crea_color_map(vis->heith, vis->width, "BF2956");
	if(!(vis->img_xr = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_xr, &vis->heith, &vis->width)))
	{
		ft_printf("error image\n");
		return (0);
	}
	return (1);
}

/*
** Read input. Create size bourd.Create map.
*/

int		read_input(t_vis *vis)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (*line == '<')
			return (0);
		if(!ft_strncmp(line, "    0", 5))
			rewrite_arr(vis);
		ft_strdel(&line);
	}
	return (0);
}

/*
** Calculates the coordinates of the Bourd in the Centr.
** heith - heith bourd, width - width bourd.
*/

void	coor_centr(int *x, int *y, int heith, int width)
{
	*y = (HEITH / 2) - (heith / 2);
	*x = (WIDTH / 2) - (width / 2);
}

/*
** Print rectangle in down whith scores.
*/

void	print_score(t_vis *vis)
{
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_score, 1040, 660);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1060, 705, 0x2056B6,
			vis->name_o);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1060, 685, 0xBF2956,
			vis->name_x);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1200, 705, 0x2056B6,
			ft_itoa(vis->score_o));
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1200, 685, 0xBF2956,
		ft_itoa(vis->score_x));
}

/*
** Print matrics of rectengle. Starn coordinate matrics (x, y).
** Count lines - row. Count colloms - col.
*/

int		print_bourd(t_vis *vis)
{
	int		i;
	int		j;
	int		y;
	int		x;
	int		x_it;
	int		y_it;

	i = -1;
	y = 0;
	read_input(vis);
	coor_centr(&x, &y, vis->row * (vis->heith + 1), vis->col * (vis->width + 1));
	y_it = y;
	x_it = x;
	print_score(vis);
	while (++i < vis->row)
	{
		j = -1;
		while (++j < vis->col)
		{
			if (vis->map[i][j] == '.')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_bourd, x_it, y_it);
			if (vis->map[i][j] == 'X')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_xr, x_it, y_it);
			if (vis->map[i][j] == 'x')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_xp, x_it, y_it);
			if (vis->map[i][j] == 'O')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_obd, x_it, y_it);
			if (vis->map[i][j] == 'o')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_obl, x_it, y_it);
			x_it += vis->width + 1;
		}
		x_it = x; 
		y_it += (vis->heith + 1);
	}
	//if (vis->map)
	//	dell_arr(vis->map);
	return (0);
}

/*
** Init background and menu.
*/

int		init_back(t_vis *vis)
{
	if(!(vis->img_back = mlx_xpm_file_to_image(vis->mlx_ptr,
			"./back3.xpm", &vis->heith, &vis->width)))
		return (0);
	return (1);
}

void	init_image(t_vis *vis)
{
	if(!(init_back(vis)))
		exit(0);
	if(!(init_image_squer(vis)))
		exit(0);
}

/*
** Init value struct.
*/

void	init_val(t_vis *vis)
{
	vis->mlx_ptr = NULL;
	vis->win_ptr = NULL;
	vis->img_back = NULL;
	vis->img_bourd = NULL;
	vis->img_obd = NULL;
	vis->img_obl = NULL;
	vis->img_xr = NULL;
	vis->img_xp = NULL;
	vis->heith = 0;
	vis->width = 0;
	vis->col = 0;
	vis->row= 0;
	vis->map = NULL;
	vis->map_xr = NULL;
	vis->map_xp = NULL;
	vis->map_obd = NULL;
	vis->map_obl = NULL;
	vis->map_bourd = NULL;
	vis->map_back = NULL;
	ft_memset(vis->name_o, '\0', 30);
	ft_memset(vis->name_x, '\0', 30);
	vis->score_o = 0;
	vis->score_x = 0;
}

char *last_name(char *name, char *line)
{
	int len;
	int i;
	int j;

	len = ft_strlen(line);
	i = len;
	j = -1;
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

int		exit_key(int key, void *par)
{
	if (key == 65307)
		exit(0);
	return (0);
}

int		main(void)
{
	int		i;
	t_vis	*vis;

	if(!(vis = create_vis()))
		exit(0);
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_back, 0, 0);
	mlx_key_hook(vis->win_ptr, exit_key, (void*)0);
	mlx_loop_hook(vis->mlx_ptr, print_bourd, vis);
	mlx_loop(vis->mlx_ptr);
}

/*
int	print_line(int x0, int x1, int y0, int y1)
{
	int		dx;
	int		dy;
	int		y;
	int		diry;
	double	er; 
	double	der; 

	dx = ABS((x1 - x0));
	dy = ABS((y1 - y0));
	der = dy;
	er = 0;
	y = y0;
	diry = y1 - y0;
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (x0 != x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y, 100);
		er = er + der;
		if (2 * er >= dx)
		{
			y = y + diry;
			er = er - dx;
		}
		x0 > x1 ? x0-- : x0++;
	}
	return (0);
}
*/
/*
** Print rectengle whith coordinates (x, y).
*/
/*
void	print_rectengle(int x, int y, int heith, int width, int color)
{
	int i;
	int j;

	i = x;
	while (++i < heith + x)
	{
		j = y - 1;
		while (++j < width + y)
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
	}
}
*/
/*
 *
int	print_hello(int key, void *par, void *par2)
{
	char *str = "Hello";
	static int i = 10;

	mlx_string_put(mlx_ptr, win_ptr, 10 + i, 200 - i, 0xFFFFFF, str);
	i += 10;
	printf("%d\n", ABS( (-3 + 1)));
	puts("Hello");
	return (0);
}
 */
